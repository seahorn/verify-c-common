#include <seahorn/seahorn.h>
#include <aws/common/linked_list.h>
#include <linked_list_helper.h>

<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
#include "nondet.h"

=======
>>>>>>> fbd5cf8... Update linked_list_reset
=======
#include "nondet.h"

>>>>>>> f3cf922... Update linked_list_next
=======
#include "nondet.h"

>>>>>>> dfccf75... return to prev state
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