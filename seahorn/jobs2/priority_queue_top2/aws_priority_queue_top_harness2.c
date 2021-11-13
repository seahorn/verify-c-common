/**
 */

#include <aws/common/priority_queue.h>
#include <priority_queue_helper.h>
#include <seahorn/seahorn.h>
#include <utils.h>

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

  /* save current state of the container structure */
  sea_tracking_on();
  sea_reset_modified((char *)&queue.container);
  sea_reset_modified((char *)queue.container.data);
  sea_reset_modified((char *)&queue.backpointers);
  sea_reset_modified((char *)queue.backpointers.data);

  /* perform operation under verification */
  void *top_val_ptr = NULL;
  aws_priority_queue_top(&queue, &top_val_ptr);

  /* assertions */
  sassert(aws_priority_queue_is_valid(&queue));
  sassert(!sea_is_modified((char *)&queue.container));
  sassert(!sea_is_modified((char *)queue.container.data));
  sassert(!sea_is_modified((char *)&queue.backpointers));
  sassert(!sea_is_modified((char *)queue.backpointers.data));
  return 0;
}

