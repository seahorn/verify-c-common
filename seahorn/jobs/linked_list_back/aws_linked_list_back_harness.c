

#include <aws/common/linked_list.h>
#include <linked_list_helper.h>
#include <seahorn/seahorn.h>

int main() {
  /* data structure */
  struct aws_linked_list list;
  struct saved_aws_linked_list to_save = {0};
  size_t size;

  sea_nd_init_aws_linked_list_from_tail(&list, &size);
  struct aws_linked_list_node *start = &list.tail;
  aws_linked_list_save_to_head(&list, size, start, &to_save);
// function only accepts non empty linked lists
#ifdef __KLEE__
  if (aws_linked_list_empty(&list))
    return 0;
#else
  assume(!aws_linked_list_empty(&list));
#endif

  /* perform operation under verification */
  struct aws_linked_list_node *back = aws_linked_list_back(&list);

  /* assertions */
  sassert(list.tail.prev == back);
  sassert(is_aws_list_unchanged_to_head(&list, &to_save));

  return 0;
}
