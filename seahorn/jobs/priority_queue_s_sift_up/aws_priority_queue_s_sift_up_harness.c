/**
 * Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
 * SPDX-License-Identifier: Apache-2.0.
 */

#include <aws/common/priority_queue.h>
#include <priority_queue_helper.h>
#include <proof_allocators.h>
#include <sea_allocators.h>
#include <seahorn/seahorn.h>
#include <utils.h>

void s_sift_up(struct aws_priority_queue *queue, size_t root);

int main(void) {
  /* Data structure */
  struct aws_priority_queue queue;
  initialize_priority_queue(&queue);

  /* Assumptions */
  assume(aws_priority_queue_is_bounded(&queue, MAX_PRIORITY_QUEUE_ITEMS,
                                       MAX_ITEM_SIZE));
  assume(aws_priority_queue_is_valid(&queue));

  /* Assume the function preconditions */
  assume(aws_priority_queue_is_valid(&queue));
  size_t root;
  root = nd_size_t();
  assume(root < queue.container.length);

  if (queue.backpointers.data) {
    /* Ensuring that just the root cell is correctly allocated is
     * not enough, as the swap requires that both the swapped
     * cells are correctly allocated.  Therefore, if swap is to
     * not be overriden, I have to ensure that all of the root
     * descendants at least are correctly allocated. For now it is
     * ensured that all of them are. */
    size_t i;
    for (i = 0; i < MAX_PRIORITY_QUEUE_ITEMS; i++) {
      if (i < queue.container.length) {
        ((struct aws_priority_queue_node **)queue.backpointers.data)[i] =
            can_fail_malloc(sizeof(struct aws_priority_queue_node));
      }
    }

    // -- ensure that loop is fully unrolled
    sassert(i >= queue.container.length);
  }

  /* Perform operation under verification */
  s_sift_up(&queue, root);

  /* Assert the postconditions */
  sassert(aws_priority_queue_is_valid(&queue));
  sassert(aws_priority_queue_backpointers_valid_deep(&queue));
  return 0;
}
