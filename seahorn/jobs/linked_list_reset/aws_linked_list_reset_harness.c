#include <seahorn/seahorn.h>
#include <aws/common/linked_list.h>
#include <linked_list_helper.h>

int main () {
    /* data structure */
    struct aws_linked_list_node node; // Preconditions require node to not be NULL
    node.next = nd_voidp();
    node.prev = nd_voidp();
    
    /* perform operation under verification */
    aws_linked_list_node_reset(&node);

    /* assertions */
    sassert(AWS_IS_ZEROED(node));
    sassert(node.next == NULL);
    sassert(node.prev == NULL);

    return 0;
}