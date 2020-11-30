/*
 *
 */

#include <seahorn/seahorn.h>
#include <aws/common/byte_buf.h>
#include <byte_buf_helper.h>
#include <utils.h>
#include <proof_allocators.h>

int main() {
    /* data structure */
    struct aws_byte_buf buf; /* Precondition: buf is non-null */
    initialize_byte_buf(&buf);

    /* parameters */
    struct aws_allocator *allocator = sea_allocator(); /* Precondition: allocator is non-null */
    size_t capacity = nd_size_t();
    assume(capacity <= MAX_INITIAL_SIZE);

    if (aws_byte_buf_init(&buf, allocator, capacity) == AWS_OP_SUCCESS) {
        /* assertions */
        sassert(aws_byte_buf_is_valid(&buf));
        sassert(buf.allocator == allocator);
        sassert(buf.len == 0);
        sassert(buf.capacity == capacity);
    }

    return 0;
}
