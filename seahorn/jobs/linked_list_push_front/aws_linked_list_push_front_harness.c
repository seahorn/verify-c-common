
#include "nondet.h"
#include <linked_list_helper.h>
#include <aws/common/linked_list.h>
#include <seahorn/seahorn.h>

int main(void) {
  /* data structure */
  struct aws_linked_list list;
  struct aws_linked_list_node to_add;
  struct aws_linked_list_node node1;
  struct aws_linked_list_node *nnode;

  // --- initialize linked list
  // head and tail are initialized
  list.head.prev = NULL; 
  list.tail.next = NULL;

  bool list_is_empty = nd_bool();
  
  if (list_is_empty) {
    nnode = &list.tail;
  } else {   
    // -- since list.tail.prev is initialized nondeterministically
    // -- it might point to head. To exclude this, we assume that list is
    // -- non-empty
    assume(!aws_linked_list_empty(&list));
    nnode = &node1;
    attach_nodeA_to_nodeB(nnode, &list.tail, false /*  directlyAttached */);
  }
  attach_nodeA_to_nodeB(&list.head, nnode, true /* directlyAttached */);

  // --- end: initialize linked list
  // 
  void *list_tail_prev_old = list.tail.prev;
  void *nnode_next_old = nnode->next;

  /* perform operation under verification */
  aws_linked_list_push_front(&list, &to_add);

  /* assertions */
  sassert(list.tail.next == NULL);
  sassert(list.head.prev == NULL);

  sassert(aws_linked_list_node_prev_is_valid(&to_add));
  sassert(aws_linked_list_node_next_is_valid(&to_add));
  sassert(list.head.next == &to_add);
  sassert(to_add.next == nnode);

  if (!list_is_empty) {
    sassert(list.tail.prev == list_tail_prev_old);
  }
  sassert(nnode->next == nnode_next_old);

  return 0;
}
