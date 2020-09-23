
#include "nondet.h"
#include <aws/common/linked_list.h>
#include <seahorn/seahorn.h>

int main(void) {
  /* data structure */
  struct aws_linked_list list;
  struct aws_linked_list_node to_add;
  struct aws_linked_list_node node1;
  struct aws_linked_list_node *pnode;

  // -- head
  list.head.prev = NULL;
  list.head.next = nd_voidp();
  void *list_head_next_old = list.head.next;

  bool list_is_empty = nd_bool();
  if (list_is_empty) {
    pnode = &list.head;
  } else {
    // -- since list.head.next is initialized nondeterministically
    // -- it might point to tail. To exclude this, we assume that list is
    // -- non-empty
    assume(!aws_linked_list_empty(&list));
    pnode = &node1;
    node1.prev = nd_voidp();
  }

  void *pnode_prev_old = pnode->prev;

  // -- tail (list of size at least 1)
  list.tail.next = NULL;
  list.tail.prev = pnode;

  // -- predecessor of tail
  pnode->next = &list.tail;

  /* Keep the old last node of the linked list */
  struct aws_linked_list_node *old_last = list.tail.prev;

  /* perform operation under verification */
  aws_linked_list_push_back(&list, &to_add);

  /* assertions */
  sassert(list.head.prev == NULL);
  sassert(list.tail.next == NULL);

  sassert(aws_linked_list_node_prev_is_valid(&to_add));
  sassert(aws_linked_list_node_next_is_valid(&to_add));
  sassert(list.tail.prev == &to_add);
  sassert(to_add.prev == old_last);

  if (!list_is_empty)
    sassert(list.head.next == list_head_next_old);
  sassert(pnode->prev == pnode_prev_old);

  return 0;
}
