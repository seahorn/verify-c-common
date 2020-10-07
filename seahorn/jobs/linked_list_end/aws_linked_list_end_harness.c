#include <seahorn/seahorn.h>
#include <aws/common/linked_list.h>
#include <linked_list_helper.h>

int main() {
    /* data structure */
    struct aws_linked_list list;
    size_t length;
    ensure_linked_list_is_allocated(&list, MAX_LINKED_LIST_ITEM_ALLOCATION, &length);

     /* Assume the preconditions. The function requires that list != NULL */
    assume(!aws_linked_list_empty(&list));

    /* perform operation under verification */
    struct aws_linked_list_node const *rval = aws_linked_list_end(&list);

    /* assertions */
    sassert(rval == &list.tail);
    sassert(sea_aws_linked_list_is_valid(&list, length));
    sassert(aws_linked_list_node_prev_is_valid(rval));
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
    sassert(rval->next == NULL);

    return 0;
=======
    sassert(aws_linked_list_node_next_is_valid(rval));
    sassert(aws_linked_list_is_valid(&list));
>>>>>>> ac80371... Add linked_list int test
=======
=======
>>>>>>> dfccf75... return to prev state
    sassert(rval->next == NULL);

    return 0;
}