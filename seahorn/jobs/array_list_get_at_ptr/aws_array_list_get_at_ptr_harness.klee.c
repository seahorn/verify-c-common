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

    /* assumptions */
    assume(aws_array_list_is_valid(&list));
    void **val = bounded_malloc(sizeof(void *));
    size_t index = nd_size_t();

    /* save current state of the data structure */
    struct aws_array_list old = list;
    struct store_byte_from_buffer old_byte;
    save_byte_from_array((uint8_t *)list.data, list.current_size, &old_byte);

    /* assume preconditions */
    assume(aws_array_list_is_valid(&list));
    assume(val);

    /* perform operation under verification */
    if (!aws_array_list_get_at_ptr(&list, val, index)) {
        /* In the case aws_array_list_get_at is successful, we can ensure the list isn't empty
         * and index is within bounds.
         */
        sassert(list.data);
        sassert(list.length > index);
    }

    /* assertions */
    sassert(aws_array_list_is_valid(&list));
    assert_array_list_equivalence(&list, &old, &old_byte);

    return 0;
}
