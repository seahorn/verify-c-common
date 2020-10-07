#include <seahorn/seahorn.h>
#include <aws/common/linked_list.h>
#include <linked_list_helper.h>

void aws_linked_list_init_harness() {
    /* data structure */
    struct aws_linked_list list;

    /* perform operation under verification */
    aws_linked_list_init(&list);

    /* assertions */
    sassert(aws_linked_list_is_valid(&list));
    sassert(aws_linked_list_empty(&list));
    sassert(list->head.next, &list->tail);
    sassert(list->tail.prev, &list->head);
}