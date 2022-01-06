/**
 * Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
 * SPDX-License-Identifier: Apache-2.0.
 */

#include <aws/common/byte_buf.h>
#include <aws/common/ring_buffer.h>

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

  /* assumptions */
  /* nondet assignment required to force true/false */
  bool is_member = nd_bool();
  if (is_member) {
    #if defined(__KLEE__) || defined(__SYMBIOTIC__)
    /* Inside ensure_byte_buf_has_allocated_buffer_member_in_ring_buf, 
     * the ring buffer requires the following be True
     * Use the following code to exclude unqualified program path
     */
    if (aws_ring_buffer_is_empty(&ring_buf))
        return 0;
    #else
      assume(!aws_ring_buffer_is_empty(&ring_buf));
    #endif
    ensure_byte_buf_has_allocated_buffer_member_in_ring_buf(&buf, &ring_buf);
  } else {
    ensure_byte_buf_has_allocated_buffer_member(&buf);
  }
  assume(aws_ring_buffer_is_valid(&ring_buf));
  assume(aws_byte_buf_is_valid(&buf));

  struct aws_ring_buffer ring_buf_old = ring_buf;
  struct aws_byte_buf buf_old = buf;

  bool result = aws_ring_buffer_buf_belongs_to_pool(&ring_buf, &buf);

  /* assertions */
  sassert(is_member == result);
  sassert(aws_ring_buffer_is_valid(&ring_buf));
  sassert(aws_byte_buf_is_valid(&buf));
  sassert(ring_buffers_are_equal(&ring_buf_old, &ring_buf));
  sassert(byte_bufs_are_equal(&buf_old, &buf));
  return 0;
}
