/*
 *
 */

#include <seahorn/seahorn.h>
#include <aws/common/array_list.h>
#include <array_list_helper.h>
#include <utils.h>

/**
 * Runtime: 5s
 */
int main() {
    /* data structure */
    struct aws_array_list list;
    initialize_bounded_array_list(&list);

    /* assumptions */
    assume(aws_array_list_is_valid(&list));
    assume(list.item_size > 0);

    /* save current state of the data structure */
    sea_tracking_on();

    /* perform operation under verification */
    size_t capacity = aws_array_list_capacity(&list);

    /* assertions */
    sassert(aws_array_list_is_valid(&list));
    sassert(!sea_is_modified((char *)&list));
    sassert(!sea_is_modified((char *)list.data));
    sassert(!sea_is_modified((char *)list.alloc));
    sassert(capacity == list.current_size / list.item_size);

    return 0;
}
