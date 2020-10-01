
#include <aws/common/linked_list.h>
#include <linked_list_helper.h>
#include <seahorn/seahorn.h>

int main(void) {
  /* data structure */
  struct aws_linked_list list;
  struct aws_linked_list_node to_add;
  struct aws_linked_list_node *pnode;
  size_t size;

  sea_nd_init_linked_list_from_back(&list, &size);
  pnode = list.tail.prev;
  void *list_head_next_old = list.head.next;
  void *pnode_prev_old = pnode->prev;

  /* perform operation under verification */
  aws_linked_list_push_back(&list, &to_add);

  /* assertions */
  sassert(list.head.prev == NULL);
  sassert(list.tail.next == NULL);

  sassert(aws_linked_list_node_prev_is_valid(&to_add));
  sassert(aws_linked_list_node_next_is_valid(&to_add));
  sassert(list.tail.prev == &to_add);
  sassert(to_add.prev == pnode);

  if (size > 0) {
    sassert(list.head.next == list_head_next_old);
  }
  sassert(pnode->prev == pnode_prev_old);

  return 0;
}
