

#include <aws/common/linked_list.h>
#include <linked_list_helper.h>
#include <seahorn/seahorn.h>

int main() {
  /* data structure */
  struct aws_linked_list list;
  struct saved_aws_linked_list to_save = {0};
  size_t size;

  sea_nd_init_aws_linked_list_from_head(&list, &size);
  struct aws_linked_list_node *start = &list.head;
  aws_linked_list_save_to_tail(&list, size, start, &to_save);

  // precondition in function does not accept empty linked list
  if (aws_linked_list_empty(&list))
    return 0;

  /* perform operation under verification */
  struct aws_linked_list_node *front = aws_linked_list_front(&list);

  /* assertions */
  sassert(list.head.next == front);
  sassert(aws_linked_list_node_prev_is_valid(front));
  sassert(aws_linked_list_node_next_is_valid(front));
  sassert(is_aws_list_unchanged_to_tail(&list, &to_save));

  return 0;
}
