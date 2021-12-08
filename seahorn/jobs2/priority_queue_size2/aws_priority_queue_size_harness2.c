/**
 */

#include <aws/common/priority_queue.h>
#include <priority_queue_helper.h>
#include <utils.h>
#include <seahorn/seahorn.h>

/**
 */
int main(void) {
    /* data structure */
    struct aws_priority_queue queue;
    initialize_priority_queue(&queue);

    /* assumptions */
    assume(aws_priority_queue_is_bounded(&queue, MAX_INITIAL_ITEM_ALLOCATION, MAX_ITEM_SIZE));
    assume(aws_priority_queue_is_valid(&queue));

    /* save state */
    sea_tracking_on();
    sea_reset_modified((char *)&queue.container);
    sea_reset_modified((char *)&queue.container.data);
    sea_reset_modified((char *)&queue.backpointers);
    sea_reset_modified((char *)&queue.backpointers.data);

    /* perform operation under verification */
    size_t size = aws_priority_queue_size(&queue);

    /* assertions */
    sassert(aws_priority_queue_is_valid(&queue));
    sassert(!sea_is_modified((char *)&queue.container));
    sassert(!sea_is_modified((char *)&queue.container.data));
    sassert(!sea_is_modified((char *)&queue.backpointers));
    sassert(!sea_is_modified((char *)&queue.backpointers.data));
    return 0;
}
