/*
 *
 */

#include <seahorn/seahorn.h>
#include <aws/common/array_list.h>
#include <array_list_helper.h>
#include <utils.h>
#include <proof_allocators.h>

/**
 * Runtime: 7s
 */
int main() {
    /* data structure */
    struct aws_array_list list;
    initialize_bounded_array_list(&list, MAX_INITIAL_SIZE,
        MAX_INITIAL_ITEM_ALLOCATION, MAX_ITEM_SIZE);
    /* parameters */
    size_t item_size = nd_size_t();
    size_t initial_item_allocation = nd_size_t();
    size_t len = nd_size_t();

    /* assumptions */
    assume(len <= MAX_INITIAL_SIZE);
    assume(initial_item_allocation > 0 && initial_item_allocation <= MAX_INITIAL_ITEM_ALLOCATION);
    assume(item_size > 0 && item_size <= MAX_ITEM_SIZE);
    assume(initial_item_allocation * item_size <= MAX_INITIAL_SIZE);
    // -- Klee could direct two paths for the following assumption:
    // -- the multiplication is overflow or not
    // -- however, when it is not overflow, Klee will hit a false assumption
    // assume(!aws_mul_size_checked(initial_item_allocation, item_size, &len));
    if (!aws_mul_size_checked(initial_item_allocation, item_size, &len)) {
        /* perform operation under verification */
        uint8_t *raw_array = bounded_malloc(len);
        struct store_byte_from_buffer old_byte;
        save_byte_from_array(raw_array, len, &old_byte);

        aws_array_list_init_static(&list, raw_array, initial_item_allocation, item_size);

        /* assertions */
        sassert(aws_array_list_is_valid(&list));
        sassert(list.alloc == NULL);
        sassert(list.item_size == item_size);
        sassert(list.length == 0);
        sassert(list.current_size == initial_item_allocation * item_size);
        assert_bytes_match((uint8_t *)list.data, raw_array, len);

        assert_byte_from_buffer_matches(raw_array, &old_byte);
    }

    return 0;
}
