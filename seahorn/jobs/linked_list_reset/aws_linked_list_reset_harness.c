#include <seahorn/seahorn.h>
#include <aws/common/linked_list.h>
#include <linked_list_helper.h>

void aws_linked_list_node_reset_harness() {
    /* data structure */
    struct aws_linked_list list;

    struct aws_linked_list_node node; // Preconditions require node to not be NULL
    node.next = nd_voidp();
    node.prev = nd_voidp();
    
    /* perform operation under verification */
    aws_linked_list_node_reset(&node);

    /* assertions */
    sassert(AWS_IS_ZEROED(node));
    sassert(node.next == NULL);
    sassert(node.prev == NULL);
}