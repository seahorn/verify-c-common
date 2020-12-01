#pragma once

#include <aws/common/ring_buffer.h>

void initialize_ring_buffer(struct aws_ring_buffer *ring_buf,
                            const size_t size);

void ensure_byte_buf_has_allocated_buffer_member_in_range(
    struct aws_byte_buf *buf, uint8_t *lo, uint8_t *hi);

void ensure_byte_buf_has_allocated_buffer_member_in_ring_buf(
    struct aws_byte_buf *buf, struct aws_ring_buffer *ring_buf);
