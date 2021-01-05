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

    initialize_bounded_array_list(&from);
    initialize_bounded_array_list(&to);

    /* assumptions */
    assume(aws_array_list_is_valid(&from));
    assume(aws_array_list_is_valid(&to));

    assume(from.item_size == to.item_size);
    // --  Klee forks two braches for from.data (NULL or !NULL)
    // --  We exit main function if from.data == NULL  
    #ifdef __KLEE__
        if (!from.data) return 0;
    #else 
        assume(from.data != NULL);
    #endif

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
