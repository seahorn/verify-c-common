/*
 *
 */

#include <seahorn/seahorn.h>
#include <aws/common/array_list.h>
#include <array_list_helper.h>
#include <utils.h>
#include <proof_allocators.h>

/**
 * Runtime: 11s
 */
int main() {
    /* data structure */
    struct aws_array_list list;
    initialize_bounded_array_list(&list, MAX_INITIAL_SIZE,
        MAX_INITIAL_ITEM_ALLOCATION, MAX_ITEM_SIZE);

    /* assumptions */
    assume(aws_array_list_is_valid(&list));

    /* save current state of the data structure */
    struct aws_array_list old = list;
    struct store_byte_from_buffer old_byte;
    save_byte_from_array((uint8_t *)list.data, list.current_size, &old_byte);

    /* perform operation under verification */
    size_t n = nd_size_t();
    aws_array_list_pop_front_n(&list, n);

    /* assertions */
    sassert(aws_array_list_is_valid(&list));
    if (n == 0) {
        assert_array_list_equivalence(&list, &old, &old_byte);
    } else {
        sassert(list.alloc == old.alloc);
        sassert(list.current_size == old.current_size);
        sassert(list.item_size == old.item_size);
        (n >= old.length) ? sassert(list.length == 0) : sassert(list.length == old.length - n);
    }

    return 0;
}
