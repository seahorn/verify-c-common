/**
 */

#include <aws/common/priority_queue.h>
#include <priority_queue_helper.h>
#include <seahorn/seahorn.h>
#include <utils.h>

int main(void) {
  /* data structure */
  struct aws_priority_queue queue;
  initialize_priority_queue(&queue);

  /* assumptions */
  assume(aws_priority_queue_is_bounded(&queue, MAX_INITIAL_ITEM_ALLOCATION,
                                       MAX_ITEM_SIZE));
  assume(aws_priority_queue_is_valid(&queue));
  assume(queue.container.item_size > 0);

  /* save current state of the container structure */
  struct aws_array_list old_container = queue.container;
  struct store_byte_from_buffer old_byte_container;
  save_byte_from_array((uint8_t *)old_container.data,
                       old_container.current_size, &old_byte_container);

  /* save current state of the backpointers structure */
  struct aws_array_list old_backpointers = queue.backpointers;
  struct store_byte_from_buffer old_byte_backpointers;
  save_byte_from_array((uint8_t *)old_backpointers.data,
                       old_backpointers.current_size, &old_byte_backpointers);

  /* perform operation under verification */
  size_t capacity = aws_priority_queue_capacity(&queue);

  /* assertions */
  sassert(aws_priority_queue_is_valid(&queue));
  sassert(capacity == queue.container.current_size / queue.container.item_size);
  assert_array_list_equivalence(&queue.container, &old_container,
                                &old_byte_container);
  assert_array_list_equivalence(&queue.backpointers, &old_backpointers,
                                &old_byte_backpointers);
  return 0;
}
