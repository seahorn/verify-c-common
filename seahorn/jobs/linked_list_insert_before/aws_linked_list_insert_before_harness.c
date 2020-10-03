#include "seahorn/seahorn.h"
#include <aws/common/linked_list.h>
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

    before.prev = &before_prev;
    before_prev.next = &before;

    /*
    XZ: ensure before.next and before_prev.prev
    does not get accessed by operation under verification;
    this is guaranteed by behaviour of nd pointer with fat mem
    */
    struct aws_linked_list_node *before_next = nd_voidp();
    struct aws_linked_list_node *before_prev_prev = nd_voidp();
    before.next = before_next;
    before_prev.prev = before_prev_prev;

    /* perform operation under verification */
    aws_linked_list_insert_before(&before, &to_add);

    /* assertions */
    sassert(aws_linked_list_node_prev_is_valid(&before));
    sassert(aws_linked_list_node_prev_is_valid(&to_add));
    sassert(aws_linked_list_node_next_is_valid(&to_add));
    sassert(aws_linked_list_node_next_is_valid(&before_prev));

    sassert(before.prev == &to_add);
    sassert(before_prev.next == &to_add);

    sassert(before.next == before_next);
    sassert(before_prev.prev == before_prev_prev);
}
