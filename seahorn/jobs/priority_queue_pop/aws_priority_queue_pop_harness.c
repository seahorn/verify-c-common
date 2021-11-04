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
  void *item = can_fail_malloc_havoc(queue.container.item_size);
  assume(item);
  assume(AWS_MEM_IS_WRITABLE(item, queue.container.item_size));

  if (queue.backpointers.data) {
    /* Assume that the two backpointers 0, len-1 are valid,
     * either by being NULL or by allocating their objects. This
     * is important for the s_swap that happens in s_remove. */
    size_t len = queue.backpointers.length;
    if (0 < len) {
      ((struct aws_priority_queue_node **)queue.backpointers.data)[0] =
          can_fail_malloc_havoc(sizeof(struct aws_priority_queue_node));
      if (0 != len - 1) {
        ((struct aws_priority_queue_node **)queue.backpointers.data)[len - 1] =
            can_fail_malloc_havoc(sizeof(struct aws_priority_queue_node));
      }
    }
  }

  /* Save the old priority queue state */
  struct aws_priority_queue old_queue = queue;

  /* Assume the preconditions */

  /* Perform operation under verification */
  if (aws_priority_queue_pop(&queue, item) == AWS_OP_SUCCESS) {
    sassert(old_queue.container.length == 1 + queue.container.length);
    if (queue.backpointers.data) {
      sassert(old_queue.backpointers.length == 1 + queue.backpointers.length);
    }
  }

  /* Sassert the postconditions */
  sassert(aws_priority_queue_is_valid(&queue));
  return 0;
}
