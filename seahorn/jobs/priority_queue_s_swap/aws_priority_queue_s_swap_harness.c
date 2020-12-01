/**
 * Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
 * SPDX-License-Identifier: Apache-2.0.
 */

#include <aws/common/priority_queue.h>
#include <priority_queue_helper.h>
#include <sea_allocators.h>
#include <seahorn/seahorn.h>
#include <utils.h>

void s_swap(struct aws_priority_queue *queue, size_t a, size_t b);

int main(void) {
  /* Data structure */
  struct aws_priority_queue queue;
  initialize_priority_queue(&queue);

  /* Assumptions */
  assume(aws_priority_queue_is_bounded(&queue, MAX_INITIAL_ITEM_ALLOCATION,
                                       MAX_ITEM_SIZE));
  assume(aws_priority_queue_is_valid(&queue));

  size_t a = nd_size_t();
  size_t b = nd_size_t();
  assume(a < queue.container.length);
  assume(b < queue.container.length);

  if (queue.backpointers.data) {
    /* Assume that the two backpointers a, b are valid, either by
     * being NULL or by allocating their objects with their correct
     * values. */
    ((struct aws_priority_queue_node **)queue.backpointers.data)[a] =
        nd_bool() ? NULL
                  : sea_malloc_safe(sizeof(struct aws_priority_queue_node));
    ((struct aws_priority_queue_node **)queue.backpointers.data)[b] =
        nd_bool() ? NULL
                  : sea_malloc_safe(sizeof(struct aws_priority_queue_node));
  }

  /* save current state of the data structure */
  struct aws_array_list old = queue.container;
  struct store_byte_from_buffer old_byte;
  save_byte_from_array((uint8_t *)old.data, old.current_size, &old_byte);

  size_t item_sz = queue.container.item_size;
  size_t offset = nd_size_t();
  assume(offset < item_sz);
  /* save a byte of the element at index a */
  struct store_byte_from_buffer old_a_byte;
  old_a_byte.index = a * item_sz + offset;
  old_a_byte.byte = ((uint8_t *)queue.container.data)[old_a_byte.index];

  /* save a byte of the element at index b */
  struct store_byte_from_buffer old_b_byte;
  old_b_byte.index = b * item_sz + offset;
  old_b_byte.byte = ((uint8_t *)queue.container.data)[old_b_byte.index];

  /* Perform operation under verification */
  s_swap(&queue, a, b);

  /* Assert the post-conditions */
  sassert(aws_priority_queue_is_valid(&queue));

  /* All the elements in the container except for a and b should stay unchanged
   */
  size_t ob_i = old_byte.index;
  if (ob_i < a * item_sz && ob_i >= (a + 1) * item_sz && ob_i < b * item_sz &&
      ob_i >= (b + 1) * item_sz) {
    assert_array_list_equivalence(&queue.container, &old, &old_byte);
  }
  /* The new element at index a must be equal to the old element in index b and
   * vice versa */
  sassert(old_a_byte.byte ==
          ((uint8_t *)queue.container.data)[old_b_byte.index]);
  sassert(old_b_byte.byte ==
          ((uint8_t *)queue.container.data)[old_a_byte.index]);
  return 0;
}
