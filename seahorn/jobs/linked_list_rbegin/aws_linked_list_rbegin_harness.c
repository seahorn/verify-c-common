#include <seahorn/seahorn.h>
#include <aws/common/linked_list.h>
#include <linked_list_helper.h>

int main(void) {
  /* data structure */
  struct aws_linked_list list;
  size_t length;
  struct saved_aws_linked_list to_save = {0};

  sea_nd_init_aws_linked_list_from_tail(&list, &length);
  struct aws_linked_list_node *start = &list.tail;
  aws_linked_list_save_to_head(&list, length, start, &to_save);
  /* perform operation under verification */
  struct aws_linked_list_node *rbegin = aws_linked_list_rbegin(&list);

  sassert(rbegin == list.tail.prev);
  sassert(aws_linked_list_node_next_is_valid(rbegin));
  sassert(length > 0 || rbegin == &list.head);
  sassert((rbegin == &list.head) || aws_linked_list_node_prev_is_valid(rbegin));
  sassert(is_aws_list_unchanged_to_head(&list, &to_save));

  return 0;
}
