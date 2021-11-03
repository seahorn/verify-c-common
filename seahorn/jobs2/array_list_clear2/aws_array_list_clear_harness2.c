/*
 * 
 */

#include <seahorn/seahorn.h>
#include <aws/common/array_list.h>
#include <array_list_helper.h>

/**
 * Runtime: 5s
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

    /* perform operation under verification */
    aws_array_list_clear(&list);

   /* assertions */
    sassert(aws_array_list_is_valid(&list));
    sassert(!sea_is_modified((char *)list.alloc));
    sassert(list.current_size == old_current_size);
    sassert(list.length == 0);
    sassert(list.item_size == old_item_size);
    sassert(!sea_is_modified((char *)list.data));
    
    return 0;
}
