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
    initialize_bounded_array_list(&list);
    size_t index = nd_size_t();

    /* assumptions */
    assume(aws_array_list_is_valid(&list));

    /* save current state of the data structure */
    sea_tracking_on();
    size_t old_current_size = list.current_size;
    size_t old_item_size = list.item_size;
    size_t old_length = list.length;

    /* perform operation under verification */
    if (aws_array_list_erase(&list, index) == AWS_OP_SUCCESS) {
        sassert(list.length == old_length - 1);
        sassert(!sea_is_modified((char *)list.alloc));
        sassert(list.current_size == old_current_size);
	sassert(list.item_size == old_item_size);
        sassert(index < old_length);
    } else {
        sassert(!sea_is_modified((char *)&list));
        sassert(!sea_is_modified((char *)list.data));
    }

    sassert(aws_array_list_is_valid(&list));

    return 0;
}
