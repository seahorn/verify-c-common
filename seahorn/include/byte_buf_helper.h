/*
 *
 */

#pragma once

#include <aws/common/byte_buf.h>

void initialize_byte_buf(struct aws_byte_buf *const buf);
void initialize_byte_cursor(struct aws_byte_cursor *const buf);

bool aws_byte_buf_is_bounded(const struct aws_byte_buf *const buf,
                             const size_t max_size);

bool aws_byte_cursor_is_bounded(const struct aws_byte_cursor *const cursor,
                                const size_t max_size);

void ensure_byte_buf_has_allocated_buffer_member(
    struct aws_byte_buf *const buf);

bool aws_byte_buf_has_allocator(const struct aws_byte_buf *const buf);

bool byte_bufs_are_equal(struct aws_byte_buf *b1, struct aws_byte_buf *b2);
