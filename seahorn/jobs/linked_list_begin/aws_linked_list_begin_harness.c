#include <seahorn/seahorn.h>
#include <aws/common/linked_list.h>
#include <linked_list_helper.h>

int main () {
    /* data structure */
    struct aws_linked_list list;
    size_t length;
    ensure_linked_list_is_allocated(&list, MAX_LINKED_LIST_ITEM_ALLOCATION, &length);

     /* Assume the preconditions. The function requires that list != NULL */
    assume(!aws_linked_list_empty(&list));

    /* perform operation under verification */
    struct aws_linked_list_node *rval = aws_linked_list_begin(&list);

    /* assertions */
    sassert(rval == list.head.next);
    sassert(sea_aws_linked_list_is_valid(&list, length));
    sassert(aws_linked_list_node_prev_is_valid(rval));
    sassert(aws_linked_list_node_next_is_valid(rval));

    return 0;
}