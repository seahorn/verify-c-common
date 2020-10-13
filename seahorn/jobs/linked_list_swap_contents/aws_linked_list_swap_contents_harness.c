#include "nondet.h"
#include <aws/common/linked_list.h>
#include <linked_list_helper.h>
#include <seahorn/seahorn.h>

int main(void) {
  /* data structure */
  struct aws_linked_list a, b;
  size_t a_len, b_len;
  sea_nd_init_aws_linked_list(&a, &a_len);
  sea_nd_init_aws_linked_list(&b, &b_len);

  /* save old linked lists */
  struct saved_aws_linked_list saved_a = {.saved_size = 0};
  struct saved_aws_linked_list saved_b = {.saved_size = 0};
  aws_linked_list_save_full(&a, a_len, a.head.next, a.tail.prev, &saved_a);
  aws_linked_list_save_full(&b, b_len, b.head.next, b.tail.prev, &saved_b);

  /* perform operation under verification */
  aws_linked_list_swap_contents(&a, &b);

  // -- basic properties of head and tail
  sassert(a.head.prev == NULL);
  sassert(a.tail.next == NULL);
  sassert(b.head.prev == NULL);
  sassert(b.tail.next == NULL);

  sassert(aws_linked_list_node_next_is_valid(&a.head));
  sassert(aws_linked_list_node_prev_is_valid(&a.tail));
  
  sassert(aws_linked_list_node_next_is_valid(&b.head));
  sassert(aws_linked_list_node_prev_is_valid(&b.tail));

  // check b has a's old content, a has b's old content
  sassert(is_aws_list_unchanged_full(&b, &saved_a));
  sassert(is_aws_list_unchanged_full(&a, &saved_b));

  return 0;
}
