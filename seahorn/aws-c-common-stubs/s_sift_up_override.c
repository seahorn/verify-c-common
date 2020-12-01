/**
 * Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
 * SPDX-License-Identifier: Apache-2.0.
 */

/**
 * FUNCTION: s_sift_up
 *
 * This function overrides the original implementation of the
 * s_sift_up function from priority_queue.h with a no_op.
 */

#include <aws/common/priority_queue.h>
#include <nondet.h>

bool s_sift_up(struct aws_priority_queue *queue, size_t index) {
  AWS_PRECONDITION(aws_priority_queue_is_valid(queue));
    AWS_PRECONDITION(index < queue->container.length);
    bool did_move = nd_bool();
    AWS_POSTCONDITION(aws_priority_queue_is_valid(queue));
    return did_move;
}
