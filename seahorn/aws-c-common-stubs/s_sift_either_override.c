/**
 * Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
 * SPDX-License-Identifier: Apache-2.0.
 */

/**
 * FUNCTION: s_sift_either
 *
 * This function overrides the original implementation of the
 * s_sift_either function from priority_queue.h with a no_op.
 *
 * It is necessary to stub out s_sift_either because in order for it
 * to work, we have to have initialized all backpointers of the
 * priority queue correctly (which needs a loop).
 *
 * It is safe to stub out s_sift_either as long as we don't make any
 * assertions on the positions of elements in the priority queue and
 * their relative values.
 *
 */

#include <nondet.h>
#include <seahorn/seahorn.h>

#include <aws/common/priority_queue.h>

void s_sift_either(struct aws_priority_queue *queue, size_t index) {
    sassert(aws_priority_queue_is_valid(queue));
    sassert(index < queue->container.length);
}
