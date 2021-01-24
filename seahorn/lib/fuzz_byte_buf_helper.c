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
