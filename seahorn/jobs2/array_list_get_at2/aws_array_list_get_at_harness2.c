/*
 *
 */

#include <seahorn/seahorn.h>
#include <aws/common/array_list.h>
#include <array_list_helper.h>
#include <utils.h>
#include <proof_allocators.h>

/**
 * Runtime: 9s
 */
int main() {
    /* data structure */
    struct aws_array_list list;
    initialize_bounded_array_list(&list);

    /* assumptions */
    assume(aws_array_list_is_valid(&list));
    void *val = bounded_malloc(list.item_size);
    size_t index = nd_size_t();

    /* assume preconditions */
    assume(aws_array_list_is_valid(&list));
    assume(val && AWS_MEM_IS_WRITABLE(val, list.item_size));

    /* save current state of the data structure */
    sea_tracking_on();

    /* perform operation under verification */
    if (!aws_array_list_get_at(&list, val, index)) {
        /* In the case aws_array_list_get_at is successful, we can ensure the list isn't empty
         * and index is within bounds.
         */
        sassert(list.data);
        sassert(list.length > index);
    }

    /* assertions */
    sassert(aws_array_list_is_valid(&list));
    sassert(!sea_is_modified((char *)&list));
    sassert(!sea_is_modified((char *)list.data));

    return 0;
}
