/*
 *
 */

#include <array_list_helper.h>
#include <aws/common/common.h>
#include <limits.h>
#include <bounds.h>
#include <nondet.h>
#include <proof_allocators.h>
#include <seahorn/seahorn.h>
#include <aws/common/array_list.h>
#include <stdint.h>
#include <stdlib.h>

void initialize_array_list(struct aws_array_list *const list) {
  list->current_size = nd_size_t();
  list->length = nd_size_t();
  list->item_size = nd_size_t();
  /// XXX Cannot do this for now
  list->data = can_fail_malloc_havoc(list->current_size);
  list->alloc = sea_allocator();
}

void initialize_bounded_array_list(struct aws_array_list *const list) {
  list->current_size = nd_size_t();
  list->item_size = nd_size_t();
  list->length = nd_size_t();
  list->data = can_fail_malloc_havoc(list->current_size);
  list->alloc = sea_allocator();
  assume(aws_array_list_is_bounded(list, 
      sea_max_array_list_len(), sea_max_array_list_item_size()));
}

bool aws_array_list_is_bounded(const struct aws_array_list *const list,
                               const size_t max_initial_item_allocation,
                               const size_t max_item_size) {
  bool item_size_is_bounded = list->item_size <= max_item_size;
  bool length_is_bounded = list->length <= max_initial_item_allocation;
  return item_size_is_bounded && length_is_bounded;
}
