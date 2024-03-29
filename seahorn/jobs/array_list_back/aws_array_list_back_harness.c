/*
 *
 */

#include <seahorn/seahorn.h>
#include <aws/common/array_list.h>
#include <array_list_helper.h>
#include <utils.h>
#include <proof_allocators.h>

int main() {

    /* data structure */
    struct aws_array_list list;
    initialize_bounded_array_list(&list);

    KLEE_ASSUME(list.item_size != 0);
    void *val = bounded_malloc_havoc(list.item_size);

    /* assumptions */
    assume(aws_array_list_is_valid(&list));

    /* save current state of the data structure */
    struct aws_array_list old = list;
    struct store_byte_from_buffer old_byte;
    save_byte_from_array((uint8_t *)list.data, list.current_size, &old_byte);

    /* assume preconditions */
    assume(aws_array_list_is_valid(&list));
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
