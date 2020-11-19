/*
 *
 */

#include <seahorn/seahorn.h>
#include <aws/common/array_list.h>
#include <array_list_helper.h>
#include <utils.h>
#include <proof_allocators.h>

bool aws_array_list_is_valid_copy(const struct aws_array_list *AWS_RESTRICT list) {
    if (!list) {
        return false;
    }
    size_t required_size = 0;
    bool required_size_is_valid =
        (aws_mul_size_checked(list->length, list->item_size, &required_size) == AWS_OP_SUCCESS);
    bool current_size_is_valid = (list->current_size >= required_size);
    bool data_is_valid = AWS_IMPLIES(list->current_size == 0, list->data == NULL) &&
                         AWS_IMPLIES(list->current_size != 0, AWS_MEM_IS_WRITABLE(list->data, list->current_size));
    bool item_size_is_valid = (list->item_size != 0);
    return required_size_is_valid && current_size_is_valid && data_is_valid && item_size_is_valid;
}

/**
 * Runtime: 19s
 */
int main() {

    /* data structure */
    struct aws_array_list list;
    initialize_bounded_array_list(&list, MAX_BLOCK_SIZE);

    /* assumptions */
    assume(aws_array_list_is_bounded(&list, MAX_INITIAL_ITEM_ALLOCATION, MAX_ITEM_SIZE));
    assume(aws_array_list_is_valid(&list));

    void *val = bounded_malloc(list.item_size);

    /* save current state of the data structure */
    struct aws_array_list old = list;
    struct store_byte_from_buffer old_byte;
    save_byte_from_array((uint8_t *)list.data, list.current_size, &old_byte);

    /* assume preconditions */
    assume(val && AWS_MEM_IS_WRITABLE(val, list.item_size));

    /* perform operation under verification */
    if (aws_array_list_back(&list, val) == AWS_OP_SUCCESS) {
        /* In the case aws_array_list_back is successful, we can ensure the list isn't empty */
        sassert(list.data != NULL);
        sassert(list.length != 0);
    }

    /* assertions */
    sassert(aws_array_list_is_valid(&list));
    assert_array_list_equivalence(&list, &old, &old_byte);

    return 0;
}
