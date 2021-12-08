/*
 *
 */

#include <seahorn/seahorn.h>
#include <aws/common/array_list.h>
#include <array_list_helper.h>
#include <utils.h>
#include <proof_allocators.h>

/**
 * Standard implementation of compare function for qsort
 */

size_t item_size;
int compare(const void *a, const void *b) {
    assume(AWS_MEM_IS_READABLE(a, item_size));// first element readable in compare function
    assume(AWS_MEM_IS_READABLE(b, item_size)); //second element readable in compare function
    return nd_int();
}

/**
 * Runtime: 12s
 */
int main() {
    /* data structure */
    struct aws_array_list list;
    initialize_bounded_array_list(&list);

    /* assumptions */
    assume(aws_array_list_is_valid(&list));

    /* save current state of the data structure */
    sea_tracking_on();

    /* perform operation under verification */
    item_size = list.item_size;
    aws_array_list_sort(&list, compare);

    /* assertions */
    sassert(aws_array_list_is_valid(&list));
    sassert(!sea_is_modified((char *)&list));
    sassert(!sea_is_modified((char *)list.data));
    sassert(!sea_is_modified((char *)list.alloc));
    return 0;
}
