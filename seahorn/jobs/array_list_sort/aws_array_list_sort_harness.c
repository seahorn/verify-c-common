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
#ifdef __KLEE__
    // For KLEE, the implementation is followed by:
    //  https://github.com/klee/klee-uclibc/blob/klee_0_9_29/libc/stdlib/stdlib.c
    // where the qsort algorithm does not randomly choose a index as pivot
    // Because CBMC expects qsort always not modifying data (post condition),
    //  qsort function for klee we need expect compare function always behave the following:
    //   < 0 The element pointed by a goes before the element pointed by b
    int comp = nd_int();
    assume(comp < 0);
    return comp;
#else
    return nd_int();
#endif
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
    struct aws_array_list old = list;
    struct store_byte_from_buffer old_byte;
    save_byte_from_array((uint8_t *)list.data, list.current_size, &old_byte);

    /* perform operation under verification */
    item_size = list.item_size;
    aws_array_list_sort(&list, compare);

    /* assertions */
    sassert(aws_array_list_is_valid(&list));
    assert_array_list_equivalence(&list, &old, &old_byte);

    return 0;
}
