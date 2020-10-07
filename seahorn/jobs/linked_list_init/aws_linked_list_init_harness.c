#include <seahorn/seahorn.h>
#include <aws/common/linked_list.h>
#include <linked_list_helper.h>

int main () {
    /* data structure */
    struct aws_linked_list list;

    /* perform operation under verification */
    aws_linked_list_init(&list);

    /* assertions */
<<<<<<< HEAD
<<<<<<< HEAD
    sassert(sea_aws_linked_list_is_valid(&list, 0));
    sassert(aws_linked_list_empty(&list));
    sassert(list.head.next == &list.tail);
    sassert(list.tail.prev == &list.head);

    return 0;
=======
    sassert(aws_linked_list_is_valid(&list));
    sassert(aws_linked_list_empty(&list));
    sassert(list->head.next, &list->tail);
    sassert(list->tail.prev, &list->head);
>>>>>>> be9808f... Add linked_list reset and next
=======
    sassert(sea_aws_linked_list_is_valid(&list, 0));
    sassert(aws_linked_list_empty(&list));
    sassert(list.head.next == &list.tail);
    sassert(list.tail.prev == &list.head);

    return 0;
>>>>>>> 09c016a... Update linked_list_init
}