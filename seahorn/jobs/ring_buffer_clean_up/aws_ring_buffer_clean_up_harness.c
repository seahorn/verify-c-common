/**
 * Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
 * SPDX-License-Identifier: Apache-2.0.
 */

#include <aws/common/byte_buf.h>
#include <aws/common/ring_buffer.h>

#include <nondet.h>
#include <proof_allocators.h>
#include <ring_buffer_helper.h>
#include <seahorn/seahorn.h>

int main(void) {
  /* parameters */
  size_t ring_buf_size = nd_size_t();
  struct aws_ring_buffer ring_buf;
  initialize_ring_buffer(&ring_buf, ring_buf_size);

  /* assumptions */
  assume(aws_ring_buffer_is_valid(&ring_buf));

  /* operation under verification */
  aws_ring_buffer_clean_up(&ring_buf);

  /* assertions */
  sassert(ring_buf.allocator == NULL);
  sassert(ring_buf.allocation == NULL);
  sassert(aws_atomic_load_ptr(&ring_buf.head) == NULL);
  sassert(aws_atomic_load_ptr(&ring_buf.tail) == NULL);
  sassert(ring_buf.allocation_end == NULL);
  return 0;
}
