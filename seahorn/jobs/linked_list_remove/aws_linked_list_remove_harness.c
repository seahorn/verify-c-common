#include <aws/common/linked_list.h>
#include "nondet.h"
#include <seahorn/seahorn.h>

int main(void) {
    /* data structure */
    struct aws_linked_list_node prev;
    struct aws_linked_list_node next;
    struct aws_linked_list_node node;

    void* prev_saved_prev;
    void* next_saved_next;

    // -- set prev to nd pointer, which makes it non-dereferencable
    prev_saved_prev = nd_voidp();
    prev.prev = prev_saved_prev;    
    prev.next = &node;

    node.prev = &prev;
    node.next = &next;

    // -- set next to nd pointer, which makes it non-dereferencable
    next_saved_next = nd_voidp();
    next.prev = &node;
    next.next = next_saved_next;


    /* perform operation under verification */
    aws_linked_list_remove(&node);

    /* sassertions */
    sassert(aws_linked_list_node_next_is_valid(&prev));
    sassert(aws_linked_list_node_prev_is_valid(&next));

    sassert(prev.next == &next);

    // -- check that fields that should be not touched are not changed
    // -- they cannot have been dereferenced because they are loaded with non-deref pointers
    sassert(prev.prev == prev_saved_prev);
    sassert(next.next == next_saved_next);

    // -- check that removed node has been properly reset
    sassert(node.next == NULL);
    sassert(node.prev == NULL);
    return 0;
}
