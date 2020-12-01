#include <aws/common/linked_list.h>
#include <linked_list_helper.h>

#include <seahorn/seahorn.h>

int main(void) {
  /* data structure */
  struct aws_linked_list list;
  size_t size;
  sea_nd_init_aws_linked_list_from_tail(&list, &size);
  struct saved_aws_linked_list to_save = {.saved_size = 0};
  if (size == 0) return 0;

  /* Keep the old last node of the linked list */
  struct aws_linked_list_node *to_pop = list.tail.prev;
  struct aws_linked_list_node *to_pop_prev = to_pop->prev;
  aws_linked_list_save_to_head(&list, size, to_pop_prev, &to_save);

  /* perform operation under verification */
  struct aws_linked_list_node *ret = aws_linked_list_pop_back(&list);

  /* assertions */
  // -- removed node is detached
  sassert(ret->next == NULL && ret->prev == NULL);
  // -- tail of list is properly updated
  sassert(is_aws_linked_list_node_attached_after(to_save.save_point, &list.tail));
  // -- list is ok
  sassert(list.head.prev == NULL);
  sassert(list.tail.next == NULL);
  // -- prev of old popped node til list.head are unchanged
  sassert(is_aws_list_unchanged_to_head(&list, &to_save));
  return 0;
}
