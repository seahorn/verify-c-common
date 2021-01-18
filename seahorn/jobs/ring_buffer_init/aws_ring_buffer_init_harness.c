/**
 */

#include <aws/common/ring_buffer.h>
#include <nondet.h>
#include <seahorn/seahorn.h>
#include <proof_allocators.h>
#include <utils.h>

int main(void) {
  /* parameters */
  struct aws_ring_buffer ring_buf;
  struct aws_allocator *allocator = sea_allocator();
  size_t size;
  size = nd_size_t();
  assume(size > 0); /* Precondition */
  KLEE_ASSUME(size <= KLEE_MAX_SIZE);

  if (aws_ring_buffer_init(&ring_buf, allocator, size) == AWS_OP_SUCCESS) {
    /* assertions */
    sassert(aws_ring_buffer_is_valid(&ring_buf));
    sassert(ring_buf.allocator == allocator);
    sassert(ring_buf.allocation_end - ring_buf.allocation == size);
  }
  return 0;
}
