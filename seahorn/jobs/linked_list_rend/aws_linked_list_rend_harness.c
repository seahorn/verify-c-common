#include <seahorn/seahorn.h>
#include <aws/common/linked_list.h>
#include <linked_list_helper.h>

int main(void) {
    /* data structure */
    struct aws_linked_list list;
    size_t length;
    sea_nd_init_aws_linked_list(&list, &length);

    /* Assume the preconditions */
    assume(sea_aws_linked_list_is_valid(&list, length));

    /* store old expected value of op under verification */
    struct aws_linked_list_node *old_rend = &list.head;

    /* Note: list can never be a NULL pointer as is_valid checks for that */

    /* perform operation under verification */
    struct aws_linked_list_node const *rend = aws_linked_list_rend(&list);

    /* assertions */
    /*
        XZ: disagree with original check:
        assert(rval == &list.head);
        *read* functions should always be checked for preservation of old value
    */
    sassert(rend == old_rend);
    sassert(old_rend == &list.head);
    sassert(sea_aws_linked_list_is_valid(&list, length));
    sassert(aws_linked_list_node_next_is_valid(rend));

}
