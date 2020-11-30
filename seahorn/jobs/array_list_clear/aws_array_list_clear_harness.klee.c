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

    initialize_bounded_array_list(&list, MAX_INITIAL_SIZE,
        MAX_INITIAL_ITEM_ALLOCATION, MAX_ITEM_SIZE);

    /* assumptions */
    assume(aws_array_list_is_valid(&list));

    /* save current state of the data structure */
    struct aws_array_list old = list;

    /* perform operation under verification */
    aws_array_list_clear(&list);

    /* assertions */
    sassert(aws_array_list_is_valid(&list));
    sassert(list.length == 0);
    sassert(list.alloc == old.alloc);
    sassert(list.current_size == old.current_size);
    sassert(list.item_size == old.item_size);
    sassert(list.data == old.data);

    return 0;
}
