/*
 *
 */

#include <seahorn/seahorn.h>
#include <aws/common/array_list.h>
#include <array_list_helper.h>
#include <utils.h>

/**
 * Runtime: 7
 */
int main() {
    /* data structure */
    struct aws_array_list from;
    initialize_bounded_array_list(&from, MAX_INITIAL_SIZE,
        MAX_INITIAL_ITEM_ALLOCATION, MAX_ITEM_SIZE);
    struct aws_array_list to;
    initialize_bounded_array_list(&to, MAX_INITIAL_SIZE,
        MAX_INITIAL_ITEM_ALLOCATION, MAX_ITEM_SIZE);

    /* assumptions */
    assume(aws_array_list_is_valid(&from));
    assume(aws_array_list_is_valid(&to));

    assume(from.alloc != NULL);
    assume(to.alloc != NULL);

    assume(from.item_size > 0);
    assume(to.item_size > 0);
    assume(from.item_size == to.item_size);

    /* save current state of the data structure */
    struct aws_array_list old_from = from;
    struct store_byte_from_buffer old_byte_from;
    save_byte_from_array((uint8_t *)from.data, from.current_size, &old_byte_from);

    struct aws_array_list old_to = to;
    struct store_byte_from_buffer old_byte_to;
    save_byte_from_array((uint8_t *)to.data, to.current_size, &old_byte_to);

    /* perform operation under verification */
    aws_array_list_swap_contents(&from, &to);

    /* assertions */
    sassert(aws_array_list_is_valid(&from));
    sassert(aws_array_list_is_valid(&to));
    assert_array_list_equivalence(&from, &old_to, &old_byte_to);
    assert_array_list_equivalence(&to, &old_from, &old_byte_from);

    return 0;
}
