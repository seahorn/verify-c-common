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
    struct aws_byte_cursor cur = aws_byte_cursor_from_array(array, length);

    /* assertions */
    sassert(aws_byte_cursor_is_valid(&cur));
    sassert(cur.len == length);
    if (cur.ptr) {
        assert_bytes_match(cur.ptr, array, cur.len);
    }

    return 0;
}
