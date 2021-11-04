/*
 *
 */

#include <array_list_helper.h>
#include <aws/common/common.h>
#include <limits.h>
#include <nondet.h>
#include <proof_allocators.h>
#include <seahorn/seahorn.h>
#include <aws/common/array_list.h>
#include <stdint.h>
#include <stdlib.h>
#include <bounds.h>

bool aws_array_list_is_bounded(const struct aws_array_list *const list,
                               const size_t max_initial_item_allocation,
                               const size_t max_item_size) {
  size_t required_size = 0;
  // Precodition to prevent (item_size * length) overflow
  bool required_size_is_not_overflow = __builtin_mul_overflow(list->length, 
      list->item_size, &required_size) == 0;
  // Precodition: (item_size * length) <= current_size
  bool required_size_is_bounded = required_size <= list->current_size;
  assume(required_size_is_not_overflow && required_size_is_bounded);
  bool item_size_is_bounded = list->item_size <= max_item_size;
  bool length_is_bounded = list->length <= max_initial_item_allocation;
  return item_size_is_bounded && length_is_bounded;
}

void initialize_bounded_array_list(struct aws_array_list *const list) {
  list->current_size = nd_size_t();
  assume(list->current_size <= klee_max_memory_size());
  list->item_size = nd_size_t();
  list->data = can_fail_malloc_havoc(list->current_size);
  if (list->data) {
    list->length = nd_size_t();
  }
  else{
    list->current_size = 0;
    list->length = 0;
  }
  assume(aws_array_list_is_bounded(list, 
      sea_max_array_list_len(), sea_max_array_list_item_size()));
  list->alloc = sea_allocator();
}
