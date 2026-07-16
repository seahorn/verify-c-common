#include "nondet.h"
#include <aws/common/linked_list.h>

#include <seahorn/seahorn.h>

extern NONDET_FN_ATTR struct aws_linked_list_node *nd_linked_list_node(void);

int main(void) {
  // -- handles the case of list of size > 1
  // -- list of size 1 must be handled differently

  /* data structure */
  struct aws_linked_list list;

  // -- partially initialize the list so that only the last element is
  // -- accessible and can be properly removed

  // -- element to be removed
  struct aws_linked_list_node node1;

  // -- tail
  list.tail.prev = &node1;
  list.tail.next = NULL;

  // -- head
  struct aws_linked_list_node *list_head_next_old = nd_linked_list_node();
  list.head.prev = NULL;
  // -- pointer that cannot be derefed
  list.head.next = list_head_next_old;

  // -- potential predecessor of node1
  struct aws_linked_list_node node2;
  struct aws_linked_list_node *node2_prev_old = nd_linked_list_node();
  // -- pointer that cannot be derefed
  node2.prev = node2_prev_old;

  // -- special case of a linked list of size 1
  bool len_one = nd_bool();

  // -- points to predecessor of node to be removed
  struct aws_linked_list_node *pnode;

  // -- if len is 1, predecessor is head, ow it is node2
  if (len_one) {
    pnode = &list.head;
  } else {
    pnode = &node2;
  }

  // -- setup predecessor to come before node1
  struct aws_linked_list_node *pnode_prev_old;
  pnode->next = &node1;
  pnode_prev_old = pnode->prev;

  node1.prev = pnode;
  node1.next = &list.tail;

  /* Assume the preconditions. The function requires that list != NULL */
  assume(!aws_linked_list_empty(&list));

  /* Keep the old last node of the linked list */
  struct aws_linked_list_node *old_prev_last = (list.tail.prev)->prev;

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
  if (!len_one)
    sassert(list.head.next == list_head_next_old);
  else
    sassert(aws_linked_list_empty(&list));
  sassert(node2.prev == node2_prev_old);

  return 0;
}
