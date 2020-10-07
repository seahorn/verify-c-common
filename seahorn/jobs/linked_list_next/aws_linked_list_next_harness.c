#include <seahorn/seahorn.h>
#include <aws/common/linked_list.h>
#include <linked_list_helper.h>

<<<<<<< HEAD
<<<<<<< HEAD
#include "nondet.h"

int main() {
=======
void aws_linked_list_next_harness() {
>>>>>>> be9808f... Add linked_list reset and next
=======
#include "nondet.h"

int main() {
>>>>>>> f3cf922... Update linked_list_next
    /* data structure */
    struct aws_linked_list list;

    struct aws_linked_list_node node;  // Preconditions require node to not be NULL
    struct aws_linked_list_node after; // Preconditions require after to not be NULL

    /* Assume the preconditions */
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> f3cf922... Update linked_list_next
    void *front = nd_voidp();
    void *back = nd_voidp();

    list.head.prev = NULL;
    list.head.next = nd_voidp();
    node.prev = front;
<<<<<<< HEAD
    node.next = &after;
    after.prev = &node;
    after.next = back;
    list.tail.prev = nd_voidp();
    list.tail.next = NULL;
=======
    node.next = &after;
    after.prev = &node;
>>>>>>> be9808f... Add linked_list reset and next
=======
    node.next = &after;
    after.prev = &node;
    after.next = back;
    list.tail.prev = nd_voidp();
    list.tail.next = NULL;
>>>>>>> f3cf922... Update linked_list_next

    /* perform operation under verification */
    struct aws_linked_list_node *rval = aws_linked_list_next(&node);

    /* assertions */
    sassert(aws_linked_list_node_next_is_valid(&node));
    sassert(aws_linked_list_node_prev_is_valid(rval));
    sassert(rval == &after);
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> f3cf922... Update linked_list_next

    sassert(rval->prev == &node);
    sassert(rval->next == back);

    sassert(node.next == rval);
    sassert(node.prev == front);

    // -- list is ok
    sassert(list.head.prev == NULL);
    sassert(list.tail.next == NULL);

    return 0;
<<<<<<< HEAD
=======
>>>>>>> be9808f... Add linked_list reset and next
=======
>>>>>>> f3cf922... Update linked_list_next
}