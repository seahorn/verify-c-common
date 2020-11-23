#pragma once

#include <aws/common/linked_list.h>

#include <stddef.h>

#include <nondet.h>
extern NONDET_FN_ATTR struct aws_linked_list_node *nd_linked_list_node(void);

/*
    Half of aws_linked_list_insert_after: sets up double linkage of
    *to_attach* after *after*, but does not link old after->next after to_attach
*/
void aws_linked_list_attach_after(struct aws_linked_list_node *after,
                                  struct aws_linked_list_node *to_attach,
                                  bool directly_attached);

/*
    For functions that only access the front node (head.next)
    Non-deterministically initialize aws_linked_list of the forms:
    If size == 0, then
    HEAD <--> TAIL
    If size == 1, then
    HEAD <--> FRONT <--> TAIL
    If size == 2, then
    HEAD <--> FRONT <--> BACK <--> TAIL
    If size > 2, then
    HEAD <--> FRONT <--> FRONT_NEXT --> nd_ptr ... nd_ptr <-- TAIL
*/
void sea_nd_init_aws_linked_list_from_head(struct aws_linked_list *list,
                                           size_t *length);

/*
    For functions that only access the back node (tail.prev)
    Non-deterministically initialize aws_linked_list of the forms:
    If size == 0, then
    HEAD <--> TAIL
    If size == 1, then
    HEAD <--> BACK <--> TAIL
    If size == 2, then
    HEAD <--> FRONT <--> BACK <--> TAIL
    If size > 2, then
    HEAD --> nd_ptr ... nd_ptr <-- BACK_PREV <--> BACK <--> TAIL
*/
void sea_nd_init_aws_linked_list_from_tail(struct aws_linked_list *list,
                                           size_t *length);

/*
    For functions that only access head and tail
    Non-deterministically initialize aws_linked_list of the forms:
    If size == 0, then
    HEAD <--> TAIL
    If size == 1, then
    HEAD <--> FRONT <--> TAIL
    If size == 2, then
    HEAD <--> FRONT <--> BACK <--> TAIL
    If size > 2, then
    HEAD <--> FRONT --> nd_ptr ... nd_ptr <-- BACK <--> TAIL
*/
void sea_nd_init_aws_linked_list(struct aws_linked_list *list,
                                 size_t *length);

// This stores a snapshot of a single linked list node
struct saved_aws_linked_list_node {
  struct aws_linked_list_node *node;
  struct aws_linked_list_node *node_prev;
  struct aws_linked_list_node *node_next;
};

// This stores a snapshot of the linked list
struct saved_aws_linked_list {
  // the size of the sub linked list which is saved
  size_t saved_size;
  // the node from where to start saving either forwards or backwards
  struct aws_linked_list_node *save_point;
  // optional save point for saving from both sides
  struct aws_linked_list_node *save_point_end;
  struct saved_aws_linked_list_node head;
  struct saved_aws_linked_list_node tail;
  // one direction saves: save upto 3 nodes - head, node1, node2 as needed OR
  // node1, node2, tail as needed
  // bi-direction saves: save up to 4 nodes:
  // head<->front...back->tail
  struct saved_aws_linked_list_node nodes[4];
};

// returns true if the final list is unmodified from start to tail
// head ... start .. tail
// To check that the sub linked list start ... tail is indeed unmodified
// we compare it with a snapshot of the array from save_point to saved_tail.
// To be used when list is saved using aws_linked_list_save_to_tail(...)
bool is_aws_list_unchanged_to_tail(struct aws_linked_list *list,
                                   struct saved_aws_linked_list *saved);

// returns true if the final list is unmodified from start to head
// head ... start .. tail
// To check that the sub linked list head ... start is indeed unmodified
// we compare it with a snapshot of the array from save_point to saved_head,
// in reverse.
// To be used when list is saved using aws_linked_list_save_to_head(...)
bool is_aws_list_unchanged_to_head(struct aws_linked_list *list,
                                   struct saved_aws_linked_list *saved);

// returns true if the final aw_linked_list *list* is unmodified from
// saved_point to saved_point_end when checking against snapshot
// *saved*.
// To be used when *saved* is created using aws_linked_list_save_full
bool is_aws_list_unchanged_full(struct aws_linked_list *list,
                                struct saved_aws_linked_list *saved);

// store a snapshot of a sub linked list starting with the node marked
// 'start'. To be used in when list is created using
// sea_nd_init_aws_linked_list_from_head(...)
void aws_linked_list_save_to_tail(struct aws_linked_list *list, size_t size,
                                  struct aws_linked_list_node *start,
                                  struct saved_aws_linked_list *to_save);

// store a snapshot of a sub linked list starting with the node marked
// 'start'. To be used in when list is created using
// sea_nd_init_aws_linked_list_from_tail(...)
void aws_linked_list_save_to_head(struct aws_linked_list *list, size_t size,
                                  struct aws_linked_list_node *start,
                                  struct saved_aws_linked_list *to_save);

// store full snapshot of *list* to *to_save*; only save 1 level deep from both
// head and tail, i.e. head.next and tail.prev
void aws_linked_list_save_full(struct aws_linked_list *list, size_t size,
                               struct aws_linked_list_node *start,
                               struct aws_linked_list_node *end,
                               struct saved_aws_linked_list *to_save);

bool is_aws_linked_list_node_attached_after(
    struct aws_linked_list_node *after, struct aws_linked_list_node *to_attach);
