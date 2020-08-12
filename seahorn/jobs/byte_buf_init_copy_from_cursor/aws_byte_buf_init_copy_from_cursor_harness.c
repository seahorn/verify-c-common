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
    struct aws_byte_buf buf;
    initialize_byte_buf(&buf);

    /* parameters */
    struct aws_allocator *allocator = _allocator();
    struct aws_byte_cursor cursor;
    initialize_byte_cursor(&cursor);

    /* assumptions */
    assume(aws_byte_cursor_is_valid(&cursor));

    if (aws_byte_buf_init_copy_from_cursor(&buf, allocator, cursor) == AWS_OP_SUCCESS) {
        /* assertions */
        sassert(aws_byte_buf_is_valid(&buf));
        sassert(aws_byte_cursor_is_valid(&cursor));
        sassert(buf.len == cursor.len);
        sassert(buf.capacity == cursor.len);
        sassert(buf.allocator == allocator);
        if (buf.buffer) {
            assert_bytes_match(buf.buffer, cursor.ptr, buf.len);
        }
    }

    return 0;
}
