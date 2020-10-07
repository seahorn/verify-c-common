#include <seahorn/seahorn.h>
#include <aws/common/linked_list.h>
#include <linked_list_helper.h>

void aws_linked_list_next_harness() {
    /* data structure */
    struct aws_linked_list list;

    struct aws_linked_list_node node;  // Preconditions require node to not be NULL
    struct aws_linked_list_node after; // Preconditions require after to not be NULL

    /* Assume the preconditions */
    node.next = &after;
    after.prev = &node;

    /* perform operation under verification */
    struct aws_linked_list_node *rval = aws_linked_list_next(&node);

    /* assertions */
    sassert(aws_linked_list_node_next_is_valid(&node));
    sassert(aws_linked_list_node_prev_is_valid(rval));
    sassert(rval == &after);
}