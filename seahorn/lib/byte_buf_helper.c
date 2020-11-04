/*
 *
 */

#include <seahorn/seahorn.h>
#include <aws/common/common.h>
#include <limits.h>
#include <byte_buf_helper.h>
#include <nondet.h>
#include <proof_allocators.h>
#include <stdint.h>
#include <stdlib.h>

void initialize_byte_buf(struct aws_byte_buf *const buf) {
    size_t len = nd_size_t();
    size_t cap = nd_size_t();
    assume(len <= cap);
    assume(cap <= MAX_BUFFER_SIZE);

    buf->len = len;
    buf->capacity = cap;
    buf->buffer = can_fail_malloc(cap * sizeof(*(buf->buffer)));
    buf->allocator = sea_allocator();
}

void initialize_byte_cursor(struct aws_byte_cursor *const cursor) {
    cursor->len = nd_size_t();
    assume(cursor->len <= MAX_BUFFER_SIZE);
    cursor->ptr = can_fail_malloc(sizeof(*(cursor->ptr)) * MAX_BUFFER_SIZE);
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
    //TODO - figure out allocator issues
    buf->allocator = sea_allocator(); 
    buf->buffer = bounded_malloc(sizeof(*(buf->buffer)) * MAX_BUFFER_SIZE);
}

bool aws_byte_buf_has_allocator(const struct aws_byte_buf *const buf) {
    return (buf->allocator == sea_allocator());
}
