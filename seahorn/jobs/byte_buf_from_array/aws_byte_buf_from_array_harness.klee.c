/*
 * 
 */

#include <seahorn/seahorn.h>
#include <aws/common/byte_buf.h>
#include <byte_buf_helper.h>
#include <utils.h>
#include <proof_allocators.h>

int main() {
    /* parameters */
    size_t length = nd_size_t();
    assume(length <= MAX_INITIAL_SIZE);
    uint8_t *array = bounded_malloc(length);

    /* operation under verification */
    struct aws_byte_buf buf = aws_byte_buf_from_array(array, length);

    /* assertions */
    sassert(aws_byte_buf_is_valid(&buf));
    sassert(buf.len == length);
    sassert(buf.capacity == length);
    sassert(buf.allocator == NULL);
    if (buf.buffer) {
        assert_bytes_match(buf.buffer, array, buf.len);
    }

    return 0;
}
