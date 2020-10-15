#include <aws/common/linked_list.h>
#include <linked_list_helper.h>

#include <seahorn/seahorn.h>

int main(void) {
  /* data structure */
  struct aws_linked_list list;
  size_t size;
  // this is the node before/(left-of) the node to be popped.
  struct aws_linked_list_node *node2;
  sea_nd_init_aws_linked_list_from_tail(&list, &size, _allocator());
  assume(size > 0);
  /* Keep the old last node of the linked list */
  struct aws_linked_list_node *old_prev_last = list.tail.prev->prev;
  struct aws_linked_list_node *node2_prev_old = list.tail.prev->prev->prev;
  struct aws_linked_list_node *list_head_next_old = list.head.next;

  /* perform operation under verification */
  struct aws_linked_list_node *ret = aws_linked_list_pop_back(&list);

  // -- removed node is detached
  sassert(ret->next == NULL);
  sassert(ret->prev == NULL);

  // -- tail of list is properly updated
  sassert(list.tail.prev == old_prev_last);

  // -- list is ok
  sassert(list.head.prev == NULL);
  sassert(list.tail.next == NULL);

  // -- accessible memory is not modified
  if (size > 1) {
    sassert(list.head.next == list_head_next_old);
  } else {
    sassert(aws_linked_list_empty(&list));
  }
  sassert(old_prev_last->prev == node2_prev_old);
  return 0;
}
