/*
 *
 */

#include <array_list_helper.h>
#include <aws/common/common.h>
#include <limits.h>
#include <nondet.h>
#include <proof_allocators.h>
#include <seahorn/seahorn.h>
#include <stdint.h>
#include <stdlib.h>

void initialize_bounded_array_list(struct aws_array_list *const list,
                                const size_t max_initial_size,
                                const size_t max_initial_item_allocation,
                                const size_t max_item_size) {
  list->current_size = nd_size_t();
  assume(list->current_size <= max_initial_size);
  list->item_size = nd_size_t();
  assume(list->item_size <= max_item_size);
  assume(list->item_size > 0);
  list->data = can_fail_malloc(list->current_size);
  if (list->data) {
    list->length = nd_size_t();
    assume(list->length <= max_initial_item_allocation);
    size_t required_size = 0;
    assume(__builtin_mul_overflow(list->length, list->item_size, 
        &required_size) == 0);
    assume(required_size <= list->current_size);
    assume(required_size <= max_initial_size);
  }
  else{
    list->current_size = 0;
    list->length = 0;
  }
  list->alloc = sea_allocator();
}
