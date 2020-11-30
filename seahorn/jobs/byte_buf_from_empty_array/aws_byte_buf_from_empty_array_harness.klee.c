/*
 * 
 */

#include <seahorn/seahorn.h>
#include <aws/common/byte_buf.h>
#include <byte_buf_helper.h>
#include <utils.h>
#include <proof_allocators.h>

int main() {
    size_t capacity = nd_size_t();
    assume(capacity <= MAX_INITIAL_SIZE);
    void *array = bounded_malloc(sizeof(*(array)) * (capacity));

    struct aws_byte_buf buf = aws_byte_buf_from_empty_array(array, capacity);
    sassert(aws_byte_buf_is_valid(&buf));
    sassert(buf.len == 0);
    sassert(buf.capacity == capacity);
    sassert(buf.allocator == NULL);
    if (buf.buffer) {
        assert_bytes_match(buf.buffer, array, capacity);
    }

    return 0;
}
