/*
 *
 */

#include <seahorn/seahorn.h>
#include <aws/common/array_list.h>
#include <array_list_helper.h>
#include <utils.h>
#include <proof_allocators.h>

/**
 * Runtime: 3min 42s
 */
int main() {
    /* data structure */
    struct aws_array_list list;
    initialize_bounded_array_list(&list);

    /* assumptions */
    assume(aws_array_list_is_valid(&list)); 
    assume(list.data != NULL);
    void *val = bounded_malloc_havoc(list.item_size);
    size_t index = nd_size_t();

    /* save current state of the data structure */
    sea_tracking_on();
    size_t old_length = list.length;

    /* assume preconditions */
    assume(aws_array_list_is_valid(&list));
    assume(val && AWS_MEM_IS_READABLE(val, list.item_size));

    /* perform operation under verification and assertions */
    if (!aws_array_list_set_at(&list, val, index)) {
        if (index > old_length)
            sassert(list.length == index + 1);
    } else {
        /* In the case aws_array_list_set_at is not successful, the list must not change */
        sassert(!sea_is_modified((char *)&list));
        sassert(!sea_is_modified((char *)list.data));
        sassert(!sea_is_modified((char *)list.alloc));
    }
    sassert(aws_array_list_is_valid(&list));

    return 0;
}
