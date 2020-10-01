#pragma once

#include <aws/common/linked_list.h>

#include <stddef.h>

// note: when directly attached is false,
// the nodes may still be directly attached
// since they are attached non-deterministically
void attach_nodeA_to_nodeB(struct aws_linked_list_node *nodeA,
                           struct aws_linked_list_node *nodeB,
                           bool directlyAttached);

// This function creates a linked list of the forms:
// If size == 0, then
// HEAD <--> TAIL
// If size == 1, then
// HEAD <--> NODE --> nd_pointer    nd_pointer <-- TAIL
// If size > 1, then
// HEAD <--> NODE1 <--> NODE2 --> nd_pointer <-- TAIL
// where nd_pointer is a non deterministic void pointer
void sea_nd_init_linked_list_from_front(struct aws_linked_list *list,
                                        size_t *size);

// This function creates a linked list of the forms:
// If size == 0, then
// HEAD <--> TAIL
// If size == 1, then
// HEAD --> nd_pointer nd_pointer <-- NODE <--> TAIL
// If size > 1, then
// HEAD --> nd_pointer nd_pointer <-- NODE1 <--> NODE2 <--> TAIL
// where nd_pointer is a non deterministic void pointer
void sea_nd_init_linked_list_from_back(struct aws_linked_list *list,
                                       size_t *size);
