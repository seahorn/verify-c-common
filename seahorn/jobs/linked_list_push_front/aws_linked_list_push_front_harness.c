
#include "nondet.h"
#include <aws/common/linked_list.h>
#include <seahorn/seahorn.h>

int main(void) {
  /* data structure */
  struct aws_linked_list list;
  struct aws_linked_list_node to_add;
  struct aws_linked_list_node node1;
  struct aws_linked_list_node *nnode;

  // -- tail; should be untouched during operation under verification
  list.tail.next = NULL;
  list.tail.prev = nd_voidp();
  void *list_tail_prev_old = list.tail.prev;

  bool list_is_empty = nd_bool();

  if (list_is_empty) {
    nnode = &list.tail;
  } else {
    // -- since list.tail.prev is initialized nondeterministically
    // -- it might point to head. To exclude this, we assume that list is
    // -- non-empty
    assume(!aws_linked_list_empty(&list));
    nnode = &node1;
    node1.next = nd_voidp();
  }

  void *nnode_next_old = nnode->next;

  // -- head; list of size at least 1
  list.head.prev = NULL;
  list.head.next = nnode;

  // -- successor of head
  nnode->prev = &list.head;

  /* Keep the old first node of the linked list */
  struct aws_linked_list_node *old_first = list.head.next;

  /* perform operation under verification */
  aws_linked_list_push_front(&list, &to_add);

  /* assertions */
  sassert(list.tail.next == NULL);
  sassert(list.head.prev == NULL);

  sassert(aws_linked_list_node_prev_is_valid(&to_add));
  sassert(aws_linked_list_node_next_is_valid(&to_add));
  sassert(list.head.next == &to_add);
  sassert(to_add.next == old_first);

  if (!list_is_empty) {
    sassert(list.tail.prev == list_tail_prev_old);
  }
  sassert(nnode->next == nnode_next_old);

  return 0;
}
