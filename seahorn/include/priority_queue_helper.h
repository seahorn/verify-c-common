/*
 *
 */

#pragma once

#include <aws/common/priority_queue.h>

void initialize_priority_queue(struct aws_priority_queue *queue);
bool aws_priority_queue_is_bounded(struct aws_priority_queue *queue,
                                   const size_t max_initial_item_allocation,
                                   const size_t max_item_size);
