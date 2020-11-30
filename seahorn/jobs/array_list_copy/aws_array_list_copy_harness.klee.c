/*
 * 
 */

#include <seahorn/seahorn.h>
#include <aws/common/array_list.h>
#include <array_list_helper.h>

/**
 * Runtime: 10s
 */
int main() {
    /* data structure */
    struct aws_array_list from;
    struct aws_array_list to;

    initialize_bounded_array_list(&from, MAX_INITIAL_SIZE,
        MAX_INITIAL_ITEM_ALLOCATION, MAX_ITEM_SIZE);
    initialize_bounded_array_list(&to, MAX_INITIAL_SIZE,
        MAX_INITIAL_ITEM_ALLOCATION, MAX_ITEM_SIZE);

    /* assumptions */
    assume(aws_array_list_is_valid(&from));
    assume(aws_array_list_is_valid(&to));

    assume(from.item_size == to.item_size);
    // --  Klee forks two braches for from.data (NULL or !NULL)
    // --  We exit main function if from.data == NULL  
    if(from.data == NULL){
        return 0;
    }

    /* perform operation under verification */
    if (!aws_array_list_copy(&from, &to)) {
        /* In the case aws_array_list_copy is successful, both lists have the same length */
        sassert(to.length == from.length);
        sassert(to.current_size >= (from.length * from.item_size));
    }

    /* assertions */
    sassert(aws_array_list_is_valid(&from));
    sassert(aws_array_list_is_valid(&to));
    sassert(from.item_size == to.item_size);

    return 0;
}
