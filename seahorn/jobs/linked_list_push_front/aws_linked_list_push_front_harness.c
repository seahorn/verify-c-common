
#include <aws/common/linked_list.h>
#include <linked_list_helper.h>
#include <seahorn/seahorn.h>

int main(void) {
  /* data structure */
  struct aws_linked_list list;
  struct aws_linked_list_node to_add;
  size_t size;

  sea_nd_init_linked_list_from_front(&list, &size);
  struct aws_linked_list_node *list_tail_prev_old = list.tail.prev;
  struct aws_linked_list_node *list_head_next_old = list.head.next;
  struct aws_linked_list_node *nnode_next_old = list_head_next_old->next;
  /* perform operation under verification */
  aws_linked_list_push_front(&list, &to_add);

  /* assertions */
  sassert(list.tail.next == NULL);
  sassert(list.head.prev == NULL);

  sassert(aws_linked_list_node_prev_is_valid(&to_add));
  sassert(aws_linked_list_node_next_is_valid(&to_add));
  sassert(list.head.next == &to_add);
  sassert(to_add.next == list_head_next_old);

  if (size > 0) {
    sassert(list.tail.prev == list_tail_prev_old);
  }
  sassert(list_head_next_old->next == nnode_next_old);

  return 0;
}
