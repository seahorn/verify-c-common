#include "nondet.h"
#include <aws/common/linked_list.h>

#include <seahorn/seahorn.h>

int main(void) {
  /* data structure */
  struct aws_linked_list list;
  size_t size;

  sea_nd_init_aws_linked_list_from_head(&list, &size);
  assume(size > 0);

  struct aws_linked_list_node *old_head_next = list.head.next->next;
  struct aws_linked_list_node *old_third_node = list.head.next->next->next;
  struct aws_linked_list_node *list_tail = list.tail.prev;

  /* perform operation under verification */
  struct aws_linked_list_node *ret = aws_linked_list_pop_front(&list);

  // -- removed node is detached
  sassert(ret->next == NULL);
  sassert(ret->prev == NULL);

  // -- head of list is properly updated
  sassert(list.head.next == old_head_next);

  // -- list is ok
  sassert(list.head.prev == NULL);
  sassert(list.tail.next == NULL);

  sassert(list.head.next == old_third_node);

  // -- accessible memory is not modified
  if (size > 1)
    sassert(list.tail.prev == list_tail);
  else
    sassert(aws_linked_list_empty(&list));
  
  return 0;
}