/**
 */

#include <aws/common/priority_queue.h>
#include <nondet.h>
#include <priority_queue_helper.h>
#include <sea_allocators.h>
#include <seahorn/seahorn.h>
#include <utils.h>
/**
 */

int main(void) {

  /* data structure */
  struct aws_priority_queue queue; /* Precondition: queue is non-null */

  /* parameters */
  size_t item_size = nd_size_t();
  size_t initial_item_allocation = nd_size_t();
  size_t len = nd_size_t();
  uint8_t *raw_array;

  /* assumptions */
  assume(initial_item_allocation > 0 &&
         initial_item_allocation <= MAX_INITIAL_ITEM_ALLOCATION);
  assume(item_size > 0 && item_size <= MAX_ITEM_SIZE);
  assume(!aws_mul_size_checked(initial_item_allocation, item_size, &len));

  /* perform operation under verification */
  raw_array = sea_malloc_safe(sizeof(uint8_t *) * len);
  aws_priority_queue_init_static(&queue, raw_array, initial_item_allocation,
                                 item_size, nondet_compare);

  /* assertions */
  sassert(aws_priority_queue_is_valid(&queue));
  sassert(queue.container.alloc == NULL);
  sassert(queue.container.item_size == item_size);
  sassert(queue.container.length == 0);
  sassert(queue.container.current_size == initial_item_allocation * item_size);
  assert_bytes_match((uint8_t *)queue.container.data, raw_array, len);
  return 0;
}
