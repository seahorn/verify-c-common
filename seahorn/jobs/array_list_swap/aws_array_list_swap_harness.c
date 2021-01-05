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
    initialize_bounded_array_list(&list);

    /* parameters */
    size_t index_a = nd_size_t();
    size_t index_b = nd_size_t();

    /* assumptions */
    assume(aws_array_list_is_valid(&list));

    #ifdef __KLEE__
        if (aws_array_list_length(&list) == 0) return 0;
    #endif
    assume(index_a < aws_array_list_length(&list));
    assume(index_b < aws_array_list_length(&list));

    /* save current state of the data structure */
    struct aws_array_list old = list;
    /* save a byte of the element at index a */
    struct store_byte_from_buffer old_a_byte;
    old_a_byte.index = index_a * old.item_size; // bytes
    old_a_byte.byte = ((uint8_t *)list.data)[old_a_byte.index];

    /* save a byte of the element at index b */
    struct store_byte_from_buffer old_b_byte;
    old_b_byte.index = index_b * old.item_size; // bytes
    old_b_byte.byte = ((uint8_t *)list.data)[old_b_byte.index];

    /* perform operation under verification */
    aws_array_list_swap(&list, index_a, index_b);

    /* assertions */
    sassert(aws_array_list_is_valid(&list));
    sassert(list.alloc == old.alloc);
    sassert(list.current_size == old.current_size);
    sassert(list.length == old.length);
    sassert(list.item_size == old.item_size);
    // data[a] == old_data[b]; data[b] == old_data[a]
    uint8_t *data_bytes = (uint8_t *)list.data;
    sassert(*(data_bytes + old_a_byte.index) == old_b_byte.byte);
    sassert(*(data_bytes + old_b_byte.index) == old_a_byte.byte);

    return 0;
}
