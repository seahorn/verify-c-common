/*
 *
 */

#include <seahorn/seahorn.h>
#include <aws/common/array_list.h>
#include <array_list_helper.h>
#include <utils.h>


int main() {
    /* parameters */
    struct aws_array_list list;
    initialize_bounded_array_list(&list, MAX_INITIAL_SIZE,
        MAX_INITIAL_ITEM_ALLOCATION, MAX_ITEM_SIZE);
    size_t index = nd_size_t();

    /* assumptions */
    assume(aws_array_list_is_valid(&list));

    /* save current state of the data structure */
    struct aws_array_list old = list;
    struct store_byte_from_buffer old_byte;
    save_byte_from_array((uint8_t *)list.data, list.current_size, &old_byte);

    /* perform operation under verification */
    if (aws_array_list_erase(&list, index) == AWS_OP_SUCCESS) {
        sassert(list.length == old.length - 1);
        sassert(list.item_size == old.item_size);
        sassert(list.alloc == old.alloc);
        sassert(list.current_size == old.current_size);
        sassert(index < old.length);
    } else {
        assert_array_list_equivalence(&list, &old, &old_byte);
    }
    sassert(aws_array_list_is_valid(&list));

    return 0;
}
