/*
 *
 */

#include <seahorn/seahorn.h>
#include <aws/common/array_list.h>
#include <array_list_helper.h>
#include <utils.h>
#include <proof_allocators.h>

/**
 * Runtime: 11s
 */
int main() {
    /* data structure */
    struct aws_array_list list;
    initialize_bounded_array_list(&list);

    /* assumptions */
    assume(aws_array_list_is_valid(&list));

    /* save current state of the data structure */
    sea_tracking_on();
    size_t old_current_size = list.current_size;
    size_t old_item_size = list.item_size;
    size_t old_length = list.length;
    
    /* perform operation under verification */
    size_t n = nd_size_t();
    aws_array_list_pop_front_n(&list, n);

    /* assertions */
    sassert(aws_array_list_is_valid(&list));
    if (n == 0 && list.length > 0) {
        sassert(!sea_is_modified((char *)&list));
        sassert(!sea_is_modified((char *)list.data));
    } else {
        sassert(list.current_size == old_current_size);
        sassert(list.item_size == old_item_size);
        (n >= old_length) ? sassert(list.length == 0) : sassert(list.length == old_length - n);
    }

    sassert(!sea_is_modified((char *)list.alloc));

    return 0;
}
