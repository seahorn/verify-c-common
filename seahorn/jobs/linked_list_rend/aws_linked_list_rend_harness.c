#include <aws/common/linked_list.h>
#include <linked_list_helper.h>
#include <seahorn/seahorn.h>

int main(void) {
  /* data structure */
  struct aws_linked_list list;
  size_t length;
  struct saved_aws_linked_list to_save = {0};

  sea_nd_init_aws_linked_list_from_head(&list, &length);
  struct aws_linked_list_node *start = &list.head;
  aws_linked_list_save_to_tail(&list, length, start, &to_save);

  /* perform operation under verification */
  struct aws_linked_list_node const *rend = aws_linked_list_rend(&list);
  sassert(rend == &list.head);
  sassert(aws_linked_list_node_next_is_valid(rend));
  sassert(is_aws_list_unchanged_to_tail(&list, &to_save));
  return 0;
}
