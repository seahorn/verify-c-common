/**
 */

#include <aws/common/priority_queue.h>
#include <priority_queue_helper.h>
#include <proof_allocators.h>
#include <sea_allocators.h>
#include <seahorn/seahorn.h>
#include <utils.h>

int s_remove_node(struct aws_priority_queue *queue, void *item, size_t index);

int main(void) {
  /* Data structure */
  struct aws_priority_queue queue;
  initialize_priority_queue(&queue);

  /* Assumptions */
  assume(aws_priority_queue_is_bounded(&queue, MAX_PRIORITY_QUEUE_ITEMS,
                                       MAX_ITEM_SIZE));
  assume(aws_priority_queue_is_valid(&queue));

  /* Assume the function preconditions */
  void *item = sea_malloc_safe(queue.container.item_size);
  size_t index = nd_size_t();
  assume(index < queue.container.length);

  struct aws_priority_queue_node *node =
      can_fail_malloc(sizeof(struct aws_priority_queue_node));

  if (queue.backpointers.data) {
    /* Assume that the two backpointers index, len-1 are valid,
     * either by being NULL or by allocating their objects. This
     * is important for the s_swap that happens in s_remove. */
    size_t len = queue.backpointers.length;
    if (index < len) {
      ((struct aws_priority_queue_node **)queue.backpointers.data)[index] =
          node;
      if (index != len - 1) {
        ((struct aws_priority_queue_node **)queue.backpointers.data)[len - 1] =
            can_fail_malloc(sizeof(struct aws_priority_queue_node));
      }
    }
  }

  /* Save the old priority queue state */
  struct aws_priority_queue old_queue = queue;

  /* Assume the preconditions */
  assume(item && AWS_MEM_IS_WRITABLE(item, queue.container.item_size));

  /* Perform operation under verification */
  if (s_remove_node(&queue, item, index) == AWS_OP_SUCCESS) {
    sassert(old_queue.container.length == 1 + queue.container.length);
    if (queue.backpointers.data) {
      sassert(old_queue.backpointers.length == 1 + queue.backpointers.length);
      if (node) {
        /* The node pointing in the element of the priority queue
         * now points to SIZE_MAX to indicate that the item was
         * removed */
        //sassert(node->current_index == SIZE_MAX);
      }
    }
  }

  /* Assert the postconditions */
  sassert(aws_priority_queue_is_valid(&queue));
  return 0;
}
