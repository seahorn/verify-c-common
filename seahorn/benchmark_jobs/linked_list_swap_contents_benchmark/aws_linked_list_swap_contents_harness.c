#include "nondet.h"
#include <aws/common/linked_list.h>
#include <seahorn/seahorn.h>

extern NONDET_FN_ATTR struct aws_linked_list_node *nd_linked_list_node(void);

void sea_nd_init_linked_list(struct aws_linked_list *list, size_t *len) {
  aws_linked_list_init(list);

  if (nd_bool()) {
    *len = 0;
    return;
  }

  if (nd_bool()) {
    *len = 1;
    struct aws_linked_list_node *node;
    node = malloc(sizeof(struct aws_linked_list_node));
    assume(node);
    aws_linked_list_push_front(list, node);
    return;
  }

  // -- list of size >1
  size_t nd_len = nd_size_t();
  assume(nd_len > 1);
  *len = nd_len;

  struct aws_linked_list_node *node1;
  struct aws_linked_list_node *node2;

  node1 = malloc(sizeof(struct aws_linked_list_node));
  node2 = malloc(sizeof(struct aws_linked_list_node));

  // -- nd_linked_list() cannot be derefed, so the list is not accessible
  // -- except for the first and last elements. This also ensures that
  // -- inaccessible elements are not touched by any function that manpulates
  // -- the linst.
  list->head.next = node1;
  node1->prev = &list->head;
  node1->next = nd_linked_list_node();

  node2->prev = nd_linked_list_node();
  node2->next = &list->tail;
  list->tail.prev = nd_linked_list_node();
}

int main(void) {
  /* data structure */
  struct aws_linked_list a, b;
  size_t a_len, b_len;

  sea_nd_init_linked_list(&a, &a_len);
  sea_nd_init_linked_list(&b, &b_len);

  struct aws_linked_list a_old, b_old;
  a_old = a;
  b_old = b;

  void *a_head_next_next_old;
  void *b_head_next_next_old;
  void *a_tail_prev_prev_old;
  void *b_tail_prev_prev_old;

  // -- the first and the last elements of the list are accessible
  // -- store values that should not be cahnged to compare with later
  if (a_len > 0) {
    a_head_next_next_old = a.head.next->next;
    a_tail_prev_prev_old = a.tail.prev->prev;
  }

  if (b_len > 0) {
    b_head_next_next_old = b.head.next->next;
    b_tail_prev_prev_old = b.tail.prev->prev;
  }

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

  if (a_len == 0) {
    // if a was empty, then b is empty after swap
    sassert(aws_linked_list_empty(&b));
  } else {
    // if a was not empty, b points to the list of a
    sassert(b.head.next == a_old.head.next);
    sassert(b.tail.prev == a_old.tail.prev);
    if (a_len > 1) {
      // if a had >1 elements, check pointers of first and last element
      sassert(b.head.next->next == a_head_next_next_old);
      sassert(b.tail.prev->prev == a_tail_prev_prev_old);
    }
  }

  // -- same check as above but for b
  if (b_len == 0) {
    sassert(aws_linked_list_empty(&a));
  } else {
    sassert(a.head.next == b_old.head.next);
    sassert(a.tail.prev == b_old.tail.prev);
    if (b_len > 1) {
      sassert(a.head.next->next == b_head_next_next_old);
      sassert(a.tail.prev->prev == b_tail_prev_prev_old);
    }
  }

  return 0;
}
