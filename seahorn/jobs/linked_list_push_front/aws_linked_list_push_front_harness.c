#include <aws/common/linked_list.h>
#include <linked_list_helper.h>
#include <seahorn/seahorn.h>

int main(void) {
  /* data structure */
  struct aws_linked_list list;
  struct aws_linked_list_node to_add;
  struct saved_aws_linked_list to_save = {0};
  size_t size;

  sea_nd_init_aws_linked_list_from_head(&list, &size);
  struct aws_linked_list_node *start = list.head.next;
  aws_linked_list_save_to_tail(&list, size, start, &to_save);

  /* perform operation under verification */
  aws_linked_list_push_front(&list, &to_add);

  /* assertions */
  sassert(list.tail.next == NULL);
  sassert(list.head.prev == NULL);
 
  sassert(aws_linked_list_node_prev_is_valid(&to_add));
  sassert(aws_linked_list_node_next_is_valid(&to_add));
  sassert(is_aws_linked_list_node_attached_after(&list.head, &to_add));
  sassert(is_aws_linked_list_node_attached_after(&to_add, to_save.save_point));
  sassert(is_aws_list_unchanged_to_tail(&list, &to_save));
  return 0;
}
