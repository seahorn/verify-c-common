#include <aws/common/linked_list.h>
#include <linked_list_helper.h>

#include <seahorn/seahorn.h>

int main(void) {
  /* data structure */
  struct aws_linked_list list;
  size_t size;
  sea_nd_init_aws_linked_list_from_head(&list, &size);
  struct saved_aws_linked_list to_save = {.saved_size = 0};
  assume(!aws_linked_list_empty(&list));
#ifdef __KLEE__
    if (size == 0) return 0;
#endif

  /* Keep the old last node of the linked list */
  struct aws_linked_list_node *to_pop = list.head.next;
  struct aws_linked_list_node *to_pop_next = to_pop->next;
  aws_linked_list_save_to_tail(&list, size, to_pop_next, &to_save);

  /* perform operation under verification */
  struct aws_linked_list_node *ret = aws_linked_list_pop_front(&list);

  /* assertions */
  // -- removed node is detached
  sassert(ret->next == NULL && ret->prev == NULL);
  // -- head of list is properly updated
  sassert(
      is_aws_linked_list_node_attached_after(&list.head, to_save.save_point));
  // -- list is ok
  sassert(list.head.prev == NULL);
  sassert(list.tail.next == NULL);
  // -- head of old popped node til list.tail are unchanged
  sassert(is_aws_list_unchanged_to_tail(&list, &to_save));
  return 0;
}
