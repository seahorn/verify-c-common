#include <nondet.h>
#include <proof_allocators.h>
#include <ring_buffer_helper.h>
#include <seahorn/seahorn.h>

#include <aws/common/byte_buf.h>

void initialize_ring_buffer(struct aws_ring_buffer *ring_buf,
                            const size_t size) {
  ring_buf->allocator = sea_allocator();
  /* The `aws_ring_buffer_init` function requires size > 0. */
  assume(0 < size);
  // assume(size <= MAX_BUFFER_SIZE);
  size_t alloc_sz = size % MAX_BUFFER_SIZE;

  ring_buf->allocation = bounded_malloc(alloc_sz);
  size_t position_head = nd_size_t();
  size_t position_tail = nd_size_t();
  assume(position_head < alloc_sz);
  assume(position_tail < alloc_sz);
  aws_atomic_store_ptr(&ring_buf->head, (ring_buf->allocation + position_head));
  aws_atomic_store_ptr(&ring_buf->tail, (ring_buf->allocation + position_tail));
  ring_buf->allocation_end = ring_buf->allocation + alloc_sz;
}

void ensure_byte_buf_has_allocated_buffer_member_in_ring_buf(
    struct aws_byte_buf *buf, struct aws_ring_buffer *ring_buf) {
  buf->allocator = nd_bool() ? NULL : sea_allocator();
  uint8_t *head = aws_atomic_load_ptr(&ring_buf->head);
  uint8_t *tail = aws_atomic_load_ptr(&ring_buf->tail);
  if (head < tail) { /* [....H    T....] */
    if (nd_bool()) {
      assume(tail < ring_buf->allocation_end);
      ensure_byte_buf_has_allocated_buffer_member_in_range(
          buf, tail, ring_buf->allocation_end);
    } else {
      assume(ring_buf->allocation < head);
      ensure_byte_buf_has_allocated_buffer_member_in_range(
          buf, ring_buf->allocation, head);
    }
  } else { /* [    T....H    ] */
    ensure_byte_buf_has_allocated_buffer_member_in_range(buf, tail, head);
  }
}

void ensure_byte_buf_has_allocated_buffer_member_in_range(
    struct aws_byte_buf *buf, uint8_t *lo, uint8_t *hi) {
  sassert(lo < hi);
  size_t space = hi - lo;
  size_t pos = nd_size_t();
  // assume(pos < space);
  pos %= space;
  buf->buffer = lo + pos;
  size_t max_capacity = hi - buf->buffer;
  sassert(0 < max_capacity);
  assume(0 < buf->capacity);
  // assume(buf->capacity <= max_capacity)
  buf->capacity %= (max_capacity + 1);
}
