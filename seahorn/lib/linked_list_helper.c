#include <linked_list_helper.h>
#include <nondet.h>
#include <proof_allocators.h>
#include <seahorn/seahorn.h>

// length is populated; to be used by caller
void ensure_linked_list_is_allocated(struct aws_linked_list *const list,
                                     size_t max_length, size_t *length) {
  size_t len = nd_size_t();
  *length = len;
  assume(len < max_length);
  list->head.prev = NULL;
  /* break two NULL stores that are optimized into memset */
  assume(max_length <= MAX_LINKED_LIST_ITEM_ALLOCATION);
  list->tail.next = NULL;

  if (len == 0) {
    list->head.next = &list->tail;
    list->tail.prev = &list->head;
    return;
  }

  struct aws_linked_list_node *curr = &list->head;

  for (size_t i = 0; i < MAX_LINKED_LIST_ITEM_ALLOCATION; i++) {
    /* This malloc should never fail as it wouldn't be valid to
     * have NULL nodes in the middle of the linked list. */
    if (i < len) {
      // struct aws_linked_list_node *node = NULL;
      struct aws_linked_list_node *node =
          bounded_malloc_pure(sizeof(struct aws_linked_list_node));
      curr->next = node;
      node->prev = curr;
      // -- node is currently the last node in the list
      node->next = &list->tail;
      list->tail.prev = node;
      curr = node;
    }
  }
}

// This is the seahorn variant of
// https://sourcegraph.com/github.com/awslabs/aws-c-common/-/blob/include/aws/common/linked_list.inl#L81
// TODO: we can make this faster by getting rid of the loop
// This can be accomplished by storing all the node addresses in an array
// and asserting properties like
// 1. Assert no inbetween node between [0,length] should be the tail
// 2. Assert only the node at 'length' + 1 index should be the tail
// 3. Assert that any node in [0, length] satisfies
// aws_linked_list_node_next_is_valid
bool sea_aws_linked_list_is_valid(const struct aws_linked_list *list,
                                  size_t length) {
  sassert(list);
  sassert(list->head.next);
  sassert(list->head.prev == NULL);
  sassert(list->tail.prev);
  sassert(list->tail.next == NULL);

  /* This could go into an infinite loop for a circular list */
  const struct aws_linked_list_node *temp = &list->head;
  /* Head must reach tail by following next pointers */
  bool head_reaches_tail = false;
  /* By satisfying the above and that edges are bidirectional, we
   * also guarantee that tail reaches head by following prev
   * pointers */
  for (size_t i = 0; i < MAX_LINKED_LIST_ITEM_ALLOCATION; i++) {
    if (i <= length) {
      if (!aws_linked_list_node_next_is_valid(temp)) {
        return false;
      }
      temp = temp->next;
    }
  }
  return temp == &list->tail;
}

void attach_nodeA_to_nodeB(struct aws_linked_list_node *nodeA, struct aws_linked_list_node *nodeB, bool directlyAttached) {
  if (directlyAttached) {
    nodeA->next = nodeB;
    nodeB->prev = nodeA;
  } else {
    nodeA->next = nd_voidp();
    nodeB->prev = nd_voidp();
  }
}
