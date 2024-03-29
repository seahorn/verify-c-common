/*
 *
 */

#include <seahorn/seahorn.h>
#include <aws/common/array_list.h>
#include <array_list_helper.h>
#include <utils.h>
#include <proof_allocators.h>

/**
 * Runtime: 2 min
 */
int main() {
    /* data structure */
    struct aws_array_list list;
    initialize_bounded_array_list(&list);

    /* assumptions */
    assume(aws_array_list_is_valid(&list));
    #ifdef __KLEE__
        if (!list.data) return 0;
    #else 
        assume(list.data != NULL);
    #endif
    void *val = bounded_malloc_havoc(list.item_size);

    /* save current state of the data structure */
    struct aws_array_list old = list;
    struct store_byte_from_buffer old_byte;
    save_byte_from_array((uint8_t *)list.data, list.current_size, &old_byte);

    /* assume preconditions */
    assume(aws_array_list_is_valid(&list));
    assume(val && AWS_MEM_IS_READABLE(val, list.item_size));

    /* perform operation under verification and assertions */
    if (!aws_array_list_push_front(&list, val)) {
        sassert(list.length == old.length + 1);
    } else {
        /* In the case aws_array_list_push_front is not successful, the list must not change */
        assert_array_list_equivalence(&list, &old, &old_byte);
    }
    sassert(aws_array_list_is_valid(&list));

    return 0;
}
