/*
 *
 */

#include <seahorn/seahorn.h>
#include <aws/common/array_list.h>
#include <array_list_helper.h>
#include <utils.h>
#include <proof_allocators.h>

/**
 * Runtime: 6s
 */
int main() {
    /* data structure */
    struct aws_array_list list;
    initialize_bounded_array_list(&list, MAX_INITIAL_SIZE,
        MAX_INITIAL_ITEM_ALLOCATION, MAX_ITEM_SIZE);

    /* parameters */
    struct aws_allocator *allocator = sea_allocator(); /* Precondition: allocator is non-null */

    size_t item_size = nd_size_t();
    assume(item_size > 0 && item_size <= MAX_ITEM_SIZE);
    size_t initial_item_allocation = nd_size_t();
    assume(initial_item_allocation <= MAX_INITIAL_ITEM_ALLOCATION);
    assume(initial_item_allocation * item_size <= MAX_INITIAL_SIZE);

    /* perform operation under verification */
    if (aws_array_list_init_dynamic(&list, allocator, initial_item_allocation, item_size) == AWS_OP_SUCCESS) {
        /* assertions */
        sassert(aws_array_list_is_valid(&list));
        sassert(list.alloc == allocator);
        sassert(list.item_size == item_size);
        sassert(list.length == 0);
        sassert(list.current_size == item_size * initial_item_allocation);
    } else {
        /*assertions */
        sassert(AWS_IS_ZEROED(list));
    }

    return 0;
}
