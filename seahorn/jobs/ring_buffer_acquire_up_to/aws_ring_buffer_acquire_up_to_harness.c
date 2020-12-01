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

  size_t minimum_size = nd_size_t();
  size_t requested_size = nd_size_t();

  /* assumptions */
  assume(requested_size >= minimum_size);
  assume(aws_ring_buffer_is_valid(&ring_buf));
  assume(aws_byte_buf_is_valid(&buf));

  /* copy of state before call */
  struct aws_ring_buffer ring_buf_old = ring_buf;

  int result = aws_ring_buffer_acquire_up_to(&ring_buf, minimum_size,
                                             requested_size, &buf);

  /* sassertions */
  sassert(aws_ring_buffer_is_valid(&ring_buf));
  if (result == AWS_OP_SUCCESS) {
    sassert(aws_byte_buf_is_valid(&buf));
    sassert(buf.capacity >= minimum_size && buf.capacity <= requested_size);
    /* aws_byte_buf always created with aws_byte_buf_from_empty_array */
    sassert(buf.len == 0);
    sassert(aws_ring_buffer_buf_belongs_to_pool(&ring_buf, &buf));
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
  sassert(ring_buf.allocator == ring_buf_old.allocator);
  sassert(ring_buf.allocation == ring_buf_old.allocation);
  sassert(ring_buf.allocation_end == ring_buf_old.allocation_end);
  return 0;
}
