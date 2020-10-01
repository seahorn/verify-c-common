#include <linked_list_helper.h>
#include <nondet.h>
#include <proof_allocators.h>
#include <seahorn/seahorn.h>

void attach_nodeA_to_nodeB(struct aws_linked_list_node *nodeA,
                           struct aws_linked_list_node *nodeB,
                           bool directlyAttached) {
  if (directlyAttached) {
    nodeA->next = nodeB;
    nodeB->prev = nodeA;
  } else {
    nodeA->next = nd_voidp();
    nodeB->prev = nd_voidp();
  }
}

void sea_nd_init_linked_list_from_front(struct aws_linked_list *list,
                                        size_t *size) {
  struct aws_linked_list_node *nnode1;
  struct aws_linked_list_node *nnode2;

  list->head.prev = NULL;
  list->tail.next = NULL;
  size_t list_size = nd_size_t();
  *size = list_size;
  if (list_size == 0) {
    attach_nodeA_to_nodeB(&list->head, &list->tail,
                          true /* directlyAttached */);
  } else if (list_size == 1) {
    nnode1 = malloc(sizeof(struct aws_linked_list_node));
    assume(nnode1);
    attach_nodeA_to_nodeB(nnode1, &list->tail, false /*  directlyAttached */);
    attach_nodeA_to_nodeB(&list->head, nnode1, true /* directlyAttached */);
    // -- since list.tail.prev is initialized nondeterministically
    // -- it might point to head. To exclude this, we assume that list is
    // -- non-empty
    assume(list->head.next != &list->tail);
    assume(list->tail.prev != &list->head);
  } else {
    nnode1 = malloc(sizeof(struct aws_linked_list_node));
    assume(nnode1);
    nnode2 = malloc(sizeof(struct aws_linked_list_node));
    assume(nnode2);
    attach_nodeA_to_nodeB(nnode2, &list->tail, false /*  directlyAttached */);
    attach_nodeA_to_nodeB(nnode1, nnode2, true /*  directlyAttached */);
    attach_nodeA_to_nodeB(&list->head, nnode1, true /* directlyAttached */);
    // -- since list.tail.prev is initialized nondeterministically
    // -- it might point to head. To exclude this, we assume that list is
    // -- non-empty
    assume(list->head.next != &list->tail);
    assume(list->tail.prev != &list->head);
  }
}

void sea_nd_init_linked_list_from_back(struct aws_linked_list *list,
                                       size_t *size) {
  struct aws_linked_list_node *nnode1;
  struct aws_linked_list_node *nnode2;

  list->head.prev = NULL;
  list->tail.next = NULL;
  size_t list_size = nd_size_t();
  *size = list_size;
  if (list_size == 0) {
    attach_nodeA_to_nodeB(&list->head, &list->tail,
                          true /* directlyAttached */);
  } else if (list_size == 1) {
    nnode1 = malloc(sizeof(struct aws_linked_list_node));
    assume(nnode1);
    attach_nodeA_to_nodeB(&list->head, nnode1, true /*  directlyAttached */);
    attach_nodeA_to_nodeB(nnode1, &list->tail, true /* directlyAttached */);
    // -- since list.tail.prev is initialized nondeterministically
    // -- it might point to head. To exclude this, we assume that list is
    // -- non-empty
    assume(list->head.next != &list->tail);
    assume(list->tail.prev != &list->head);
  } else {
    // -- since list.tail.prev is initialized nondeterministically
    // -- it might point to head. To exclude this, we assume that list is
    // -- non-empty
    nnode1 = malloc(sizeof(struct aws_linked_list_node));
    assume(nnode1);
    nnode2 = malloc(sizeof(struct aws_linked_list_node));
    assume(nnode2);
    attach_nodeA_to_nodeB(&list->head, nnode1, false /*  directlyAttached */);
    attach_nodeA_to_nodeB(nnode1, nnode2, true /*  directlyAttached */);
    attach_nodeA_to_nodeB(nnode2, &list->tail, true /* directlyAttached */);
    // -- since list.tail.prev is initialized nondeterministically
    // -- it might point to head. To exclude this, we assume that list is
    // -- non-empty
    assume(list->head.next != &list->tail);
    assume(list->tail.prev != &list->head);
  }
}
