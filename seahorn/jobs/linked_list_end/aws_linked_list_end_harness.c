#include <aws/common/linked_list.h>
#include <linked_list_helper.h>
#include <seahorn/seahorn.h>

int main(void) {
  /* data structure */
  struct aws_linked_list list;
  size_t length;
  struct saved_aws_linked_list to_save = {0};

  sea_nd_init_aws_linked_list_from_tail(&list, &length);
  struct aws_linked_list_node *start = &list.tail;
  aws_linked_list_save_to_head(&list, length, start, &to_save);
  /* perform operation under verification */
  const struct aws_linked_list_node *end = aws_linked_list_end(&list);

  sassert(end == &list.tail);
  sassert(is_aws_list_unchanged_to_head(&list, &to_save));
}
