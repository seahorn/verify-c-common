
#include <aws/common/linked_list.h>
#include <linked_list_helper.h>
#include <seahorn/seahorn.h>

int main(void) {
  /* data structure */
  struct aws_linked_list list;
  struct aws_linked_list_node to_add;
  struct saved_aws_linked_list to_save = {0};
  size_t size;

  sea_nd_init_aws_linked_list_from_tail(&list, &size, _allocator());
  struct aws_linked_list_node *start = list.tail.prev;
  aws_linked_list_save_to_head(&list, size, start, &to_save);

  /* perform operation under verification */
  aws_linked_list_push_back(&list, &to_add);

  /* assertions */
  sassert(list.head.prev == NULL);
  sassert(list.tail.next == NULL);

  sassert(aws_linked_list_node_prev_is_valid(&to_add));
  sassert(aws_linked_list_node_next_is_valid(&to_add));
  sassert(is_aws_linked_list_node_attached_after(&to_add, &list.tail));
  sassert(is_aws_linked_list_node_attached_after(to_save.save_point, &to_add));
  sassert(is_aws_list_unchanged_to_head(&list, &to_save));
  return 0;
}
