/*
 *
 */

#include <seahorn/seahorn.h>
#include <aws/common/array_list.h>
#include <array_list_helper.h>
#include <utils.h>

/**
 * Runtime: 9s
 */
int main() {
    /* data structure */
    struct aws_array_list list;
    initialize_bounded_array_list(&list);

    /* assumptions */
    assume(aws_array_list_is_valid(&list));

    /* save current state of the data structure */
    sea_tracking_on();
    size_t old_item_size = list.item_size;
    size_t old_length = list.length;
    size_t old_current_size = list.current_size;

    /* perform operation under verification */
    size_t index = nd_size_t();
    KLEE_ASSUME(index <= KLEE_MAX_SIZE);
    if (!aws_array_list_ensure_capacity(&list, index)) {
        /* assertions */
        sassert(aws_array_list_is_valid(&list));
        sassert(list.item_size == old_item_size);
        sassert(!sea_is_modified((char *)list.alloc));
        sassert(list.length == old_length);
        sassert(list.current_size >= old_current_size);
    } else {
        /* In the case aws_array_list_ensure_capacity is not successful, the list must not change */
        sassert(!sea_is_modified((char *)&list));
        sassert(!sea_is_modified((char *)list.data));
    }

    return 0;
}
