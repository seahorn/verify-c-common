/*
 *
 */

#include <seahorn/seahorn.h>
#include <aws/common/common.h>
#include <limits.h>
#include <array_list_helper.h>
#include <nondet.h>
#include <proof_allocators.h>
#include <stdint.h>
#include <stdlib.h>

void initialize_array_list(struct aws_array_list *const list) {
    list->current_size = nd_size_t();
    list->length = nd_size_t();
    list->item_size = nd_size_t();
    /// XXX Cannot do this for now
    //list->data = bounded_malloc(list->current_size);
    list->data = bounded_malloc(MAX_INITIAL_ITEM_ALLOCATION * MAX_ITEM_SIZE);
    list->alloc = nd_voidp();//_allocator();
}
bool aws_array_list_is_bounded(
    const struct aws_array_list *const list,
    const size_t max_initial_item_allocation,
    const size_t max_item_size) {
    bool item_size_is_bounded = list->item_size <= max_item_size;
    bool length_is_bounded = list->length <= max_initial_item_allocation;
    return item_size_is_bounded && length_is_bounded;
}


