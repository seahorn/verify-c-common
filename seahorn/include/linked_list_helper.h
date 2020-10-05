#pragma once

#include <aws/common/linked_list.h>

#include <stddef.h>

void ensure_linked_list_is_allocated(struct aws_linked_list *const list, size_t max_length, size_t *length);

bool sea_aws_linked_list_is_valid(const struct aws_linked_list *list, size_t length);

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
void sea_nd_init_aws_linked_list_from_front(struct aws_linked_list *list,
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
void sea_nd_init_aws_linked_list_from_back(struct aws_linked_list *list,
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
