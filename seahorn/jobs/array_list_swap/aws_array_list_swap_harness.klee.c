/*
 *
 */

#include <seahorn/seahorn.h>
#include <aws/common/array_list.h>
#include <array_list_helper.h>
#include <utils.h>

/**
 * Runtime: 11s
 */
int main() {
    /* data structure */
    struct aws_array_list list;
    initialize_bounded_array_list(&list, MAX_BLOCK_SIZE);

    /* parameters */
    size_t index_a = nd_size_t();
    size_t index_b = nd_size_t();

    /* assumptions */
    assume(aws_array_list_is_bounded(&list, MAX_INITIAL_ITEM_ALLOCATION, MAX_ITEM_SIZE));
    assume(aws_array_list_is_valid(&list));

    /* save current state of the data structure */
    struct aws_array_list old = list;

    if (aws_array_list_length(&list) > 0) {
        assume(index_a < aws_array_list_length(&list));
        assume(index_b < aws_array_list_length(&list));

        /* perform operation under verification */
        aws_array_list_swap(&list, index_a, index_b);
    }

    /* assertions */
    sassert(aws_array_list_is_valid(&list));
    sassert(list.alloc == old.alloc);
    sassert(list.current_size == old.current_size);
    sassert(list.length == old.length);
    sassert(list.item_size == old.item_size);

    return 0;
}
