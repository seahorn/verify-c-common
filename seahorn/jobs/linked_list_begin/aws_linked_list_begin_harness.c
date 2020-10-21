#include <seahorn/seahorn.h>
#include <aws/common/linked_list.h>
#include <linked_list_helper.h>

int main () {
    /* data structure */
    struct aws_linked_list list;
    size_t size;
    struct saved_aws_linked_list to_save = {0};

    sea_nd_init_aws_linked_list_from_head(&list, &size);
    struct aws_linked_list_node *start = list.head.next;
    aws_linked_list_save_to_tail(&list, size, start, &to_save);

     /* Assume the preconditions. The function requires that list != NULL */
    assume(size > 0);

    /* perform operation under verification */
    struct aws_linked_list_node *rval = aws_linked_list_begin(&list);

    /* assertions */
    sassert(rval == start);
    sassert(is_aws_list_unchanged_to_tail(&list, &to_save));
    return 0;
}