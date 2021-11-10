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
    initialize_bounded_array_list(&list);

    /* assumptions */
    assume(aws_array_list_is_valid(&list));

    /* remove some elements before shrinking the data structure */
    size_t n = nd_size_t();
    aws_array_list_pop_front_n(&list, n);

    /* save current state of the data structure */
    sea_tracking_on();

    /* perform operation under verification and assertions */
    if (!aws_array_list_shrink_to_fit(&list)) {
        sassert(
            (list.current_size == 0 && list.data == NULL) ||
            (list.data != NULL && list.current_size == list.length * list.item_size));
    } else {
        /* In the case aws_array_list_shrink_to_fit is not successful, the list must not change */
        sassert(!sea_is_modified((char *)&list));
        sassert(!sea_is_modified((char *)list.data));
        sassert(!sea_is_modified((char *)list.alloc));
    }
    sassert(aws_array_list_is_valid(&list));

    return 0;
}
