#include <seahorn/seahorn.h>
#include <aws/common/linked_list.h>
#include <linked_list_helper.h>

int main(void) {
    /* data structure */
    struct aws_linked_list list;
    size_t length;
    sea_nd_init_aws_linked_list_from_back(&list, &length);

    /* Assume the preconditions */
    assume(sea_aws_linked_list_is_valid(&list, length));

    /* Store expected output node in the linked list */
    struct aws_linked_list_node *old_rbegin = list.tail.prev;

    /* Note: list can never be a NULL pointer as is_valid checks for that */

    /* perform operation under verification */
    struct aws_linked_list_node *rbegin = aws_linked_list_rbegin(&list);

    /* assertions */
    /*
    XZ: disagree with original check:
    assert(rval == list.tail.prev);
    a wrong (and potentially malicious) impl of aws_linked_list_rbegin could
    have replaced list.tail.prev to random other node, and returned it instead;
    this kind of *read* functions should always be checked for preservation of
    old value
    */
    sassert(rbegin == old_rbegin);
    sassert(old_rbegin == list.tail.prev);
    sassert(sea_aws_linked_list_is_valid(&list, length));
    sassert(aws_linked_list_node_next_is_valid(rbegin));
    sassert(length > 0 || rbegin == &list.head);
    sassert((rbegin == &list.head) || aws_linked_list_node_prev_is_valid(rbegin));
}
