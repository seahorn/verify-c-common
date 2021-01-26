#include <assert.h>
#include <bounds.h>
#include <byte_buf_helper.h>
#include <proof_allocators.h>

void initialize_byte_buf(struct aws_byte_buf *const buf) {
  size_t max_size = sea_max_buffer_size();
  size_t len = nd_size_t();
  size_t cap = nd_size_t();
  // cap <= max_size
  cap %= max_size;
  // len <= cap
  cap = cap == 0 ? 1 : cap;
  len %= cap;

  buf->len = len;
  buf->capacity = cap;
  buf->buffer = can_fail_malloc(cap * sizeof(*(buf->buffer)));
  buf->allocator = sea_allocator();
}

void initialize_byte_cursor(struct aws_byte_cursor *const cursor) {
  size_t max_buffer_size = sea_max_buffer_size();
  cursor->len = nd_size_t();
  // cursor->len <= max_buffer_size
  cursor->len %= max_buffer_size;
  cursor->ptr = can_fail_malloc(sizeof(*(cursor->ptr)) * max_buffer_size);
}

bool aws_byte_buf_is_bounded(const struct aws_byte_buf *const buf,
                             const size_t max_size) {
  return (buf->capacity <= max_size);
}

bool aws_byte_cursor_is_bounded(const struct aws_byte_cursor *const cursor,
                                const size_t max_size) {
  return cursor->len <= max_size;
}
