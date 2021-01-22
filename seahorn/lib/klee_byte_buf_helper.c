/*
 *
 */

#include <limits.h>
#include <stdint.h>
#include <stdlib.h>

#include <aws/common/common.h>
#include <seahorn/seahorn.h>

#include <bounds.h>
#include <byte_buf_helper.h>
#include <nondet.h>
#include <proof_allocators.h>

void initialize_byte_buf(struct aws_byte_buf *const buf) {
    size_t cap = nd_size_t();
    assume(cap <= sea_max_buffer_size());
    buf->buffer = can_fail_malloc(cap * sizeof(*(buf->buffer)));
    if (buf->buffer) {
        size_t len = nd_size_t();
        assume(len <= cap);
        buf->len = len;
        buf->capacity = cap;
    }
    else {
        buf->len = 0;
        buf->capacity = 0;
    }
    buf->allocator = sea_allocator();
}

void initialize_byte_cursor(struct aws_byte_cursor *const cursor) {
    size_t max_buffer_size = sea_max_buffer_size();
    cursor->ptr = can_fail_malloc(sizeof(*(cursor->ptr)) * max_buffer_size);
    if (cursor->ptr){
        cursor->len = nd_size_t();
        assume(cursor->len <= max_buffer_size);
    }
    else cursor->len = 0;
}

bool aws_byte_buf_is_bounded(
    const struct aws_byte_buf *const buf,
    const size_t max_size) {
    return (buf->capacity <= max_size);
}

bool aws_byte_cursor_is_bounded(
    const struct aws_byte_cursor *const cursor,
    const size_t max_size) {
    return cursor->len <= max_size;
}

void ensure_byte_buf_has_allocated_buffer_member(
    struct aws_byte_buf *const buf) {
    buf->allocator = sea_allocator();
    if (buf) {
        buf->buffer = bounded_malloc(sizeof(*(buf->buffer)) * buf->capacity);
        size_t len = nd_size_t();
        assume(len <= buf->capacity);
        buf->len = len;
    }
}

bool aws_byte_buf_has_allocator(const struct aws_byte_buf *const buf) {
    return (buf->allocator == sea_allocator());
}

bool byte_bufs_are_equal(struct aws_byte_buf *b1, struct aws_byte_buf *b2) {
  if (!b1 || !b2)
    return b1 == b2;

  return b1->len == b2->len && b1->buffer == b2->buffer &&
         b1->capacity == b2->capacity && b1->allocator == b2->allocator;
}