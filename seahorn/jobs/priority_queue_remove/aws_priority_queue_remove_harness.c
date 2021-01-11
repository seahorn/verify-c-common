/**
 */

#include <aws/common/priority_queue.h>

#include <priority_queue_helper.h>
#include <proof_allocators.h>
#include <sea_allocators.h>
#include <seahorn/seahorn.h>
#include <utils.h>

int main() {
  /* Data structure */
  struct aws_priority_queue queue;
  initialize_priority_queue(&queue);

  /* Assumptions */
  #ifdef __KLEE__
    // Inside aws_priority_queue_is_valid, the priority queue require the following be True
    // Use the following code to exclude unqualified program path
    if (!(queue.backpointers.item_size == sizeof(struct aws_priority_queue_node *)))
      return 0;
  #endif
  assume(aws_priority_queue_is_bounded(&queue, MAX_INITIAL_ITEM_ALLOCATION,
                                       MAX_ITEM_SIZE));
  assume(aws_priority_queue_is_valid(&queue));

  /* Assume the function preconditions */
  assume(aws_priority_queue_is_valid(&queue));
  void *item = can_fail_malloc(queue.container.item_size);
  assume(item);
  assume(AWS_MEM_IS_WRITABLE(item, queue.container.item_size));
  struct aws_priority_queue_node *backpointer =
      can_fail_malloc(sizeof(struct aws_priority_queue_node));
  assume(backpointer);
  assume(AWS_MEM_IS_READABLE(backpointer, sizeof(struct aws_priority_queue_node)));

  if (queue.backpointers.data && backpointer) {
    /* Assume that the two backpointers index, len-1 are valid,
     * either by being NULL or by allocating their objects. This
     * is important for the s_swap that happens in s_remove. */
    size_t index = backpointer->current_index;
    size_t len = queue.backpointers.length;
    if (index < len) {
      ((struct aws_priority_queue_node **)queue.backpointers.data)[index] =
          can_fail_malloc(sizeof(struct aws_priority_queue_node));
      if (index != len - 1) {
        ((struct aws_priority_queue_node **)queue.backpointers.data)[len - 1] =
            can_fail_malloc(sizeof(struct aws_priority_queue_node));
      }
    }
  }

  /* Save the old priority queue state */
  struct aws_priority_queue old_queue = queue;

  /* Perform operation under verification */
  if (aws_priority_queue_remove(&queue, item, backpointer) == AWS_OP_SUCCESS) {
    sassert(old_queue.container.length == 1 + queue.container.length);
    if (queue.backpointers.data) {
      sassert(old_queue.backpointers.length == 1 + queue.backpointers.length);
    }
  }

  /* Sassert the postconditions */
  sassert(aws_priority_queue_is_valid(&queue));
  return 0;
}
