/**
 * Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
 * SPDX-License-Identifier: Apache-2.0.
 */

#include <aws/common/byte_buf.h>
#include <aws/common/ring_buffer.h>
#include <cbmc/ring_buffer_abstract_states.h>

#include <byte_buf_helper.h>
#include <nondet.h>
#include <proof_allocators.h>
#include <ring_buffer_helper.h>
#include <seahorn/seahorn.h>

int main(void) {
  /* parameters */
  struct aws_byte_buf buf;
  initialize_byte_buf(&buf);
  assume(aws_byte_buf_is_valid(&buf));

  size_t ring_buf_size = nd_size_t();
  struct aws_ring_buffer ring_buf;
  initialize_ring_buffer(&ring_buf, ring_buf_size);

  size_t requested_size = nd_size_t();

  /* assumptions */
  assume(aws_ring_buffer_is_valid(&ring_buf));

  /* copy of state before call */
  struct aws_ring_buffer ring_buf_old = ring_buf;

  int result = aws_ring_buffer_acquire(&ring_buf, requested_size, &buf);

  /* sassertions */
  uint8_t *old_head = aws_atomic_load_ptr(&ring_buf_old.head);
  uint8_t *old_tail = aws_atomic_load_ptr(&ring_buf_old.tail);
  uint8_t *new_head = aws_atomic_load_ptr(&ring_buf.head);
  uint8_t *new_tail = aws_atomic_load_ptr(&ring_buf.tail);
  if (result == AWS_OP_SUCCESS) {
    sassert(aws_byte_buf_is_valid(&buf));
    sassert(buf.capacity == requested_size);
    sassert(AWS_MEM_IS_WRITABLE(buf.buffer, buf.capacity));
    /* aws_byte_buf always created with aws_byte_buf_from_empty_array */
    sassert(buf.len == 0);
    sassert(aws_ring_buffer_buf_belongs_to_pool(&ring_buf, &buf));
    if (aws_ring_buffer_is_empty(&ring_buf_old)) {
      sassert(new_head == ring_buf_old.allocation + requested_size);
      sassert(new_tail == ring_buf_old.allocation);
    } else {
      sassert(new_head == ring_buf_old.allocation + requested_size ||
              new_head == old_head + requested_size);
      sassert(new_tail == old_tail);
    }
    sassert(AWS_IMPLIES(is_empty_state(&ring_buf_old),
                        is_front_valid_state(&ring_buf)));
    sassert(AWS_IMPLIES(is_front_valid_state(&ring_buf_old),
                        is_front_valid_state(&ring_buf)));
    sassert(AWS_IMPLIES(is_middle_valid_state(&ring_buf_old),
                        is_middle_valid_state(&ring_buf) ||
                            is_ends_valid_state(&ring_buf)));
    sassert(AWS_IMPLIES(is_ends_valid_state(&ring_buf_old),
                        is_ends_valid_state(&ring_buf)));
    sassert(!(is_front_valid_state(&ring_buf_old) &&
              is_middle_valid_state(&ring_buf)));
  } else {
    sassert(ring_buffers_are_equal(&ring_buf, &ring_buf_old));
  }
  sassert(aws_ring_buffer_is_valid(&ring_buf));
  sassert(ring_buf.allocator == ring_buf_old.allocator);
  sassert(ring_buf.allocation == ring_buf_old.allocation);
  sassert(ring_buf.allocation_end == ring_buf_old.allocation_end);
  return 0;
}
