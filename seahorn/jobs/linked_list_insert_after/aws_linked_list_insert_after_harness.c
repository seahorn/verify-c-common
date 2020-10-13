#include "seahorn/seahorn.h"
#include <aws/common/linked_list.h>
#include <linked_list_helper.h>
#include "nondet.h"

/*
Before operation under verification:

    ?<-->to_add<-->?
    after_prev<-->after<-->after_next<-->after_next_next

After operation under verification
aws_linked_list_insert_after(&after, &to_add):

    after_prev<-->after<-->to_add<-->after_next<-->after_next_next

*/
int main(void) {
    /* data structure */
    struct aws_linked_list_node after;
    struct aws_linked_list_node after_next;
    struct aws_linked_list_node to_add;

    aws_linked_list_attach_after(&after, &after_next, true);

    /*
    XZ: ensure after.prev and after_next.next
    does not get accessed by operation under verification;
    this is guaranteed by behaviour of nd pointer with fat mem
    */
    struct aws_linked_list_node *after_prev = nd_voidp();
    struct aws_linked_list_node *after_next_next = nd_voidp();
    after.prev = after_prev;
    after_next.next = after_next_next;

    /* perform operation under verification */
    aws_linked_list_insert_after(&after, &to_add);

    /* assertions */
    sassert(is_aws_linked_list_node_attached_after(&after, &to_add));
    sassert(is_aws_linked_list_node_attached_after(&to_add, &after_next));

    /*
    XZ: ensure after.prev and after_next.next remain unchanged
    */
    sassert(after.prev == after_prev);
    sassert(after_next.next == after_next_next);

}
