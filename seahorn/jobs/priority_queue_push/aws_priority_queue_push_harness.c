/**
 */

#include <aws/common/priority_queue.h>
#include <priority_queue_helper.h>
#include <proof_allocators.h>
#include <sea_allocators.h>
#include <seahorn/seahorn.h>

int main() {
  /* Data structure */
  struct aws_priority_queue queue;
  initialize_priority_queue(&queue);

  /* Assumptions */
  assume(aws_priority_queue_is_bounded(&queue, MAX_INITIAL_ITEM_ALLOCATION,
                                       MAX_ITEM_SIZE));
  assume(aws_priority_queue_is_valid(&queue));

  /* Assumptions */
  void *item = can_fail_malloc(queue.container.item_size);
  assume(item);
  assume(AWS_MEM_IS_WRITABLE(item, queue.container.item_size));

  /* Perform operation under verification */
  aws_priority_queue_push(&queue, item);

  /* Assert the postconditions */
  sassert(aws_priority_queue_is_valid(&queue));
  return 0;
}
