/**
 */

#include <aws/common/priority_queue.h>
#include <nondet.h>
#include <priority_queue_helper.h>
#include <sea_allocators.h>
#include <proof_allocators.h>
#include <seahorn/seahorn.h>
#include <utils.h>
int main(void) {
  /* data structure */
  struct aws_priority_queue queue; /* Precondition: queue is non-null */

  /* parameters */
  struct aws_allocator *allocator = sea_allocator();
  size_t item_size = nd_size_t();
  size_t initial_item_allocation = nd_size_t();
  size_t len = nd_size_t();

  /* assumptions */
  KLEE_ASSUME(__builtin_mul_overflow(initial_item_allocation, 
        item_size, &len) == 0 && len <= KLEE_MAX_SIZE);
  assume(initial_item_allocation <= MAX_INITIAL_ITEM_ALLOCATION);
  assume(item_size > 0 && item_size <= MAX_ITEM_SIZE);
  assume(!aws_mul_size_checked(initial_item_allocation, item_size, &len));

  /* perform operation under verification */
  #ifdef __KLEE__
    uint8_t *raw_array = bounded_malloc_havoc(sizeof(uint8_t) * len);
    if (!raw_array) return 0; // assume(raw_array)
  #else 
    uint8_t *raw_array = sea_malloc_safe(sizeof(uint8_t) * len);
  #endif

  if (aws_priority_queue_init_dynamic(&queue, allocator,
                                      initial_item_allocation, item_size,
                                      nondet_compare) == AWS_OP_SUCCESS) {
    /* assertions */
    sassert(aws_priority_queue_is_valid(&queue));
    sassert(queue.container.alloc == allocator);
    sassert(queue.container.item_size == item_size);
    sassert(queue.container.length == 0);
    sassert(
        (queue.container.data == NULL && queue.container.current_size == 0) ||
        (queue.container.data && queue.container.current_size ==
                                     (initial_item_allocation * item_size)));
  } else {
    /* assertions */
    sassert(AWS_IS_ZEROED(queue.container));
    sassert(AWS_IS_ZEROED(queue.backpointers));
  }
  return 0;
}
