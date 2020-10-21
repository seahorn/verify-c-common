#include <seahorn/seahorn.h>
#include <aws/common/linked_list.h>
#include <linked_list_helper.h>

#include "nondet.h"

int main () {
    /* data structure */
    struct aws_linked_list_node node; // Preconditions require node to not be NULL
    void *front = nd_voidp();
    void *back = nd_voidp();
    node.next = front;
    node.prev = back;
    
    /* perform operation under verification */
    aws_linked_list_node_reset(&node);

    /* assertions */
    sassert(AWS_IS_ZEROED(node));
    sassert(node.next == NULL);
    sassert(node.prev == NULL);

    return 0;
}