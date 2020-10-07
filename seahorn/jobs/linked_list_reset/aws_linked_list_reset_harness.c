#include <seahorn/seahorn.h>
#include <aws/common/linked_list.h>
#include <linked_list_helper.h>

<<<<<<< HEAD
<<<<<<< HEAD
#include "nondet.h"

int main () {
    /* data structure */
    struct aws_linked_list_node node; // Preconditions require node to not be NULL
    void *front = nd_voidp();
    void *back = nd_voidp();
    node.next = front;
    node.prev = back;
=======
void aws_linked_list_node_reset_harness() {
=======
int main () {
>>>>>>> fbd5cf8... Update linked_list_reset
    /* data structure */
    struct aws_linked_list_node node; // Preconditions require node to not be NULL
<<<<<<< HEAD
    node.next = nd_voidp();
    node.prev = nd_voidp();
>>>>>>> be9808f... Add linked_list reset and next
=======
    void *front = nd_voidp();
    void *back = nd_voidp();
    node.next = front;
    node.prev = back;
>>>>>>> 56b5555... Update linked_list_reset
    
    /* perform operation under verification */
    aws_linked_list_node_reset(&node);

    /* assertions */
    sassert(AWS_IS_ZEROED(node));
    sassert(node.next == NULL);
    sassert(node.prev == NULL);
<<<<<<< HEAD
<<<<<<< HEAD

    return 0;
=======
>>>>>>> be9808f... Add linked_list reset and next
=======

    return 0;
>>>>>>> fbd5cf8... Update linked_list_reset
}