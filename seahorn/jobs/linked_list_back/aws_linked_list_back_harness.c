

#include <seahorn/seahorn.h>
#include <aws/common/linked_list.h>
#include <linked_list_helper.h>



int main() {
  /* data structure */
  struct aws_linked_list list;
  struct aws_linked_list_node to_add;
  // struct aws_linked_list_node node1;
  // struct aws_linked_list_node *nnode;
  size_t size;

  sea_nd_init_linked_list_from_back(&list, &size);
  assume(size > 0);

  // TODO: add seahorn support that 1) struct aws_linked_list is never written
  // to 2) nnode is never written to
  struct aws_linked_list_node *old_head = &list.head;
  struct aws_linked_list_node *old_tail = &list.tail;
  struct aws_linked_list_node *pnode_old = old_tail->prev;
  struct aws_linked_list_node *pnode_old_next = pnode_old->next;
  struct aws_linked_list_node *pnode_old_prev = pnode_old->prev;

  /* perform operation under verification */
  struct aws_linked_list_node *back = aws_linked_list_back(&list);

  /* assertions */
  sassert(&list.head == old_head);
  sassert(&list.tail == old_tail);
  sassert(list.tail.prev == pnode_old);
  sassert(list.head.next == old_head->next);
  sassert(aws_linked_list_node_next_is_valid(back));
  sassert(back->prev == pnode_old->prev);
  sassert(back == pnode_old);

  return 0;
}
