#include <seahorn/seahorn.h>
#include <aws/common/linked_list.h>
#include <linked_list_helper.h>

#include "nondet.h"

int main() {
    /* data structure */
    struct aws_linked_list list;

    struct aws_linked_list_node node;  // Preconditions require node to not be NULL
    struct aws_linked_list_node after; // Preconditions require after to not be NULL

    /* Assume the preconditions */
    void *front = nd_voidp();
    void *back = nd_voidp();

    list.head.prev = NULL;
    list.head.next = nd_voidp();
    node.prev = front;
    node.next = &after;
    after.prev = &node;
    after.next = back;
    list.tail.prev = nd_voidp();
    list.tail.next = NULL;

    /* perform operation under verification */
    struct aws_linked_list_node *rval = aws_linked_list_next(&node);

    /* assertions */
    sassert(aws_linked_list_node_next_is_valid(&node));
    sassert(aws_linked_list_node_prev_is_valid(rval));
    sassert(rval == &after);

    sassert(rval->prev == &node);
    sassert(rval->next == back);

    sassert(node.next == rval);
    sassert(node.prev == front);

    // -- list is ok
    sassert(list.head.prev == NULL);
    sassert(list.tail.next == NULL);

    return 0;
}