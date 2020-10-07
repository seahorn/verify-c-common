#include <aws/common/linked_list.h>
#include <proof_helpers/make_common_data_structures.h>

void aws_linked_list_end_harness() {
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
    sassert(aws_linked_list_is_valid(&list));
}