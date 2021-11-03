/*
 *
 */

#include <array_list_helper.h>
#include <aws/common/array_list.h>
#include <config.h>
#include <proof_allocators.h>
#include <seahorn/seahorn.h>
#include <utils.h>

/**
 * Runtime: 7s
 */
int main() {
    /* data structure */
    struct aws_array_list list;
    initialize_bounded_array_list(&list);

    /* parameters */
    size_t item_size = nd_size_t();
    size_t initial_item_allocation = nd_size_t();
    size_t len = nd_size_t();
    
    size_t required_size = 0;
    assume(initial_item_allocation > 0 && initial_item_allocation <= MAX_INITIAL_ITEM_ALLOCATION);
    assume(item_size > 0 && item_size <= MAX_ITEM_SIZE);
    assume(!aws_mul_size_checked(initial_item_allocation, item_size, &len));
    
    /* save current state of the parameters */
    sea_tracking_on();

    /* operation under verification */
    uint8_t *raw_array = bounded_malloc(len); 
    aws_array_list_init_static(&list, raw_array, initial_item_allocation, item_size);

    /* assertions */
    sassert(aws_array_list_is_valid(&list));
    sassert(list.alloc == NULL);
    sassert(list.item_size == item_size);
    sassert(list.length == 0);
    sassert(list.current_size == initial_item_allocation * item_size);
    assert_bytes_match((uint8_t *)list.data, raw_array, len);

    sassert(!sea_is_modified((char *)raw_array));

    return 0;
}
