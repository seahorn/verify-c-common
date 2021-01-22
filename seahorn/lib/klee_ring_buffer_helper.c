#include <ring_buffer_helper.h>
#include <nondet.h>
#include <proof_allocators.h>
#include <seahorn/seahorn.h>

#include <aws/common/byte_buf.h>

void initialize_ring_buffer(struct aws_ring_buffer *ring_buf,
                            const size_t size) {
  ring_buf->allocator = sea_allocator();
  /* The `aws_ring_buffer_init` function requires size > 0. */
  assume(0 < size && size <= KLEE_MAX_SIZE);
  ring_buf->allocation = bounded_malloc(size);
  size_t position_head = nd_size_t();
  size_t position_tail = nd_size_t();
  assume(position_head < size);
  assume(position_tail < size);
  aws_atomic_store_ptr(&ring_buf->head, (ring_buf->allocation + position_head));
  aws_atomic_store_ptr(&ring_buf->tail, (ring_buf->allocation + position_tail));
  uint8_t *head = (uint8_t *)aws_atomic_load_ptr(&ring_buf->head);
  uint8_t *tail = (uint8_t *)aws_atomic_load_ptr(&ring_buf->tail);
  /* if head points-to the first element of the buffer then tail must too */
  assume((head != ring_buf->allocation) || (tail == ring_buf->allocation));
  ring_buf->allocation_end = ring_buf->allocation + size;
}

/* the function required byte buf passed
 * points to ring buffer within range [lo,hi]
 * Klee requires more work to strengthen capacity and length
 * because byte->buffer is now changed compared with initialization
 * However, to ensure byte buffer is not NULL
 * The capacity of new buffer must be greater than 0
 * The symb exec will failed if assign a new symb value by nd_size_t()
 * Only allow capacity is a maximum one.
 */
void ensure_byte_buf_has_allocated_buffer_member_in_range(
    struct aws_byte_buf *buf, uint8_t *lo, uint8_t *hi) {
  sassert(lo < hi);
  size_t space = hi - lo;
  size_t pos = nd_size_t();
  assume(pos < space);
  buf->buffer = lo + pos;
  size_t max_capacity = hi - buf->buffer;
  sassert(0 < max_capacity);
  buf->capacity = max_capacity;
  assume(0 < buf->capacity && buf->capacity <= max_capacity);
  size_t len = nd_size_t();
  assume(len <= buf->capacity);
  buf->len = len;
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

bool ring_buffers_are_equal(struct aws_ring_buffer *r1,
                            struct aws_ring_buffer *r2) {
  if (!r1 || !r2)
    return r1 == r2;

  bool res = r1->allocator == r2->allocator &&
             r1->allocation == r2->allocation &&
             r1->allocation_end == r2->allocation_end;
  if (!res)
    return false;
  uint8_t *r1_head = aws_atomic_load_ptr(&r1->head);
  uint8_t *r1_tail = aws_atomic_load_ptr(&r1->tail);

  uint8_t *r2_head = aws_atomic_load_ptr(&r2->head);
  uint8_t *r2_tail = aws_atomic_load_ptr(&r2->tail);

  return r1_head == r2_head && r1_tail == r2_tail;
}
