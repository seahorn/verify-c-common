/**
 */

#include <aws/common/byte_buf.h>
#include <aws/common/ring_buffer.h>
#include <byte_buf_helper.h>
#include <cbmc/ring_buffer_abstract_states.h>

#include <nondet.h>
#include <proof_allocators.h>
#include <seahorn/seahorn.h>
#include <ring_buffer_helper.h>

int main(void) {
  /* parameters */
  struct aws_byte_buf buf;
  initialize_byte_buf(&buf);
  assume(aws_byte_buf_is_valid(&buf));

  size_t ring_buf_size = nd_size_t();
  struct aws_ring_buffer ring_buf;
  initialize_ring_buffer(&ring_buf, ring_buf_size);

  /* assumptions */
  assume(!aws_ring_buffer_is_empty(&ring_buf));
  assume(aws_ring_buffer_is_valid(&ring_buf));
  ensure_byte_buf_has_allocated_buffer_member_in_ring_buf(&buf, &ring_buf);

  /* copy of state before call */
  struct aws_ring_buffer ring_buf_old = ring_buf;
  struct aws_byte_buf buf_old = buf;
  sea_tracking_on();
  sea_reset_modified((char *)&ring_buf);

  /* operation under verification */
  aws_ring_buffer_release(&ring_buf, &buf);

  /* assertions */
  uint8_t *old_head = aws_atomic_load_ptr(&ring_buf_old.head);
  uint8_t *old_tail = aws_atomic_load_ptr(&ring_buf_old.tail);
  uint8_t *new_head = aws_atomic_load_ptr(&ring_buf.head);
  uint8_t *new_tail = aws_atomic_load_ptr(&ring_buf.tail);
  sassert(aws_ring_buffer_is_valid(&ring_buf));
  sassert(ring_buf.allocator == ring_buf_old.allocator);
  sassert(ring_buf.allocation == ring_buf_old.allocation);
  sassert(new_head == old_head);
  sassert(new_tail == buf_old.buffer + buf_old.capacity);
  sassert(ring_buf.allocation_end == ring_buf_old.allocation_end);
  sassert(buf.allocator == NULL);
  sassert(buf.buffer == NULL);
  sassert(buf.len == 0);
  sassert(buf.capacity == 0);
  sassert(AWS_IMPLIES(is_front_valid_state(&ring_buf_old),
                      is_empty_state(&ring_buf) ||
                          is_middle_valid_state(&ring_buf)));
  sassert(AWS_IMPLIES(is_middle_valid_state(&ring_buf_old),
                      is_empty_state(&ring_buf) ||
                          is_middle_valid_state(&ring_buf) ||
                          is_ends_valid_state(&ring_buf)));
  sassert(AWS_IMPLIES(is_ends_valid_state(&ring_buf_old),
                      is_empty_state(&ring_buf) ||
                          is_middle_valid_state(&ring_buf) ||
                          is_ends_valid_state(&ring_buf)));
  return 0;
}
