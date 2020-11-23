#include "seahorn/seahorn.h"
#include <aws/common/linked_list.h>
#include <linked_list_helper.h>
#include "nondet.h"

/*
Before operation under verification:

    ?<-->to_add<-->?
    before_prev_prev<-->before_prev<-->before<-->before_next

After operation under verification
aws_linked_list_insert_before(&before, &to_add):

    before_prev_prev<-->before_prev<-->to_add<-->before<-->before_next

*/
int main(void) {
    /* data structure */
    struct aws_linked_list_node before;
    struct aws_linked_list_node before_prev;
    struct aws_linked_list_node to_add;

    aws_linked_list_attach_after(&before_prev, &before, true);

    /*
    XZ: ensure before.next and before_prev.prev
    does not get accessed by operation under verification;
    this is guaranteed by behaviour of nd pointer with fat mem
    */
    struct aws_linked_list_node *before_next = nd_linked_list_node();
    struct aws_linked_list_node *before_prev_prev = nd_linked_list_node();
    before.next = before_next;
    before_prev.prev = before_prev_prev;

    /* perform operation under verification */
    aws_linked_list_insert_before(&before, &to_add);

    /* assertions */
    sassert(is_aws_linked_list_node_attached_after(&before_prev, &to_add));
    sassert(is_aws_linked_list_node_attached_after(&to_add, &before));

    /*
    ensure before.next and before_prev.prev remain unchanged
    */
    sassert(before.next == before_next);
    sassert(before_prev.prev == before_prev_prev);
}
