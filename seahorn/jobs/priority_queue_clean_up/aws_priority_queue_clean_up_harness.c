/**
 */

#include "utils.h"
#include <aws/common/priority_queue.h>
#include <priority_queue_helper.h>
#include <seahorn/seahorn.h>

/**
 */
int main(void) {
  /* data structure */
  struct aws_priority_queue queue;
  initialize_priority_queue(&queue);
  /* assumptions */
  assume(aws_priority_queue_is_bounded(&queue, MAX_INITIAL_ITEM_ALLOCATION,
                                       MAX_ITEM_SIZE));
  assume(aws_priority_queue_is_valid(&queue));

  /* perform operation under verification */
  aws_priority_queue_clean_up(&queue);

  /* assertions */
  size_t container_size = queue.container.item_size * queue.container.length;
  assert_all_zeroes(queue.container.data, container_size);
  size_t backpointers_size =
      queue.backpointers.item_size * queue.backpointers.length;
  assert_all_zeroes(queue.backpointers.data, backpointers_size);
  return 0;
}
