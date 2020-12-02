/*
 *
 */

#include <seahorn/seahorn.h>
#include <aws/common/array_list.h>
#include <array_list_helper.h>
#include <utils.h>
#include <proof_allocators.h>

/**
 * Runtime: 13s
 */
int main() {
    /* data structure */
    struct aws_array_list list;
    initialize_bounded_array_list(&list, MAX_INITIAL_SIZE,
        MAX_INITIAL_ITEM_ALLOCATION, MAX_ITEM_SIZE);

    /* assumptions */
    assume(aws_array_list_is_valid(&list));

    /* remove some elements before shrinking the data structure */
    size_t n = nd_size_t();
    aws_array_list_pop_front_n(&list, n);

    /* save current state of the data structure */
    struct aws_array_list old = list;
    struct store_byte_from_buffer old_byte;
    save_byte_from_array((uint8_t *)list.data, list.current_size, &old_byte);

    /* perform operation under verification and assertions */
    if (!aws_array_list_shrink_to_fit(&list)) {
        sassert(
            (list.current_size == 0 && list.data == NULL) ||
            (list.data != NULL && list.current_size == list.length * list.item_size));
    } else {
        /* In the case aws_array_list_shrink_to_fit is not successful, the list must not change */
        assert_array_list_equivalence(&list, &old, &old_byte);
    }
    sassert(aws_array_list_is_valid(&list));

    return 0;
}
