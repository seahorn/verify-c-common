#include "nondet.h"
#include <aws/common/linked_list.h>

#include <seahorn/seahorn.h>

int main(void) {
  // -- handles the case of list of size > 1
  // -- list of size 1 must be handled differently

  /* data structure */
  struct aws_linked_list list;

  // -- partially initialize the list so that only the last element is
  // -- accessible and can be properly removed

  // -- element to be removed
  struct aws_linked_list_node node1;

  // -- head 
  list.head.next = &node1;
  list.head.prev = NULL;

  // -- tail
  void *list_tail_prev_old = nd_voidp();
  list.tail.next = NULL;
  // -- pointer that cannot be derefed
  list.tail.prev = list_tail_prev_old;

  // -- potential successor of node1
  struct aws_linked_list_node node2;
  void *node2_next_old = nd_voidp();
  // -- pointer that cannot be derefed
  node2.next = node2_next_old;

  // -- special case of a linked list of size 1
  bool len_one = nd_bool();

  // -- points to successor of node to be removed
  struct aws_linked_list_node *pnode;

  // -- if len is 1, successor is head, ow it is node2
  if (len_one) {
    pnode = &list.head;
  } else {
    pnode = &node2;
  }

  // -- setup successor to come after node1
  struct aws_linked_list_node *pnode_next_old;
  pnode->prev = &node1;
  pnode_next_old = pnode->next;

  node1.next = pnode;
  node1.prev = &list.head;

  /* Assume the preconditions. The function requires that list != NULL */
  assume(!aws_linked_list_empty(&list));

  /* Keep the old first node */
  struct aws_linked_list_node *old_next_first = (list.head.next)->next;

  /* perform operation under verification */
  struct aws_linked_list_node *ret = aws_linked_list_pop_front(&list);

  // -- removed node is detached
  sassert(ret->next == NULL);
  sassert(ret->prev == NULL);

  // -- head of list is properly updated
  sassert(list.head.next == old_next_first);

  // -- list is ok
  sassert(list.head.prev == NULL);
  sassert(list.tail.next == NULL);

  // -- accessible memory is not modified
  if (!len_one)
    sassert(list.tail.prev == list_tail_prev_old);
  else
    sassert(aws_linked_list_empty(&list));
  sassert(node2.next == node2_next_old);

  return 0;
}