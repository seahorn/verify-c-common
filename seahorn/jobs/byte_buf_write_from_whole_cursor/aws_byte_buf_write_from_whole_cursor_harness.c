/*
 * 
 */

#include <seahorn/seahorn.h>
#include <aws/common/byte_buf.h>
#include <byte_buf_helper.h>
#include <utils.h>

int main() {
    /* parameters */
    struct aws_byte_buf buf;
    initialize_byte_buf(&buf);
    struct aws_byte_cursor src;
    initialize_byte_cursor(&src);

    /* assumptions */
    assume(aws_byte_buf_is_valid(&buf));
    assume(aws_byte_cursor_is_valid(&src));

    /* save current state of the parameters */
    struct aws_byte_buf buf_old = buf;
    struct store_byte_from_buffer old_byte_from_buf;
    save_byte_from_array(buf.buffer, buf.len, &old_byte_from_buf);
    struct aws_byte_cursor src_old = src;
    struct store_byte_from_buffer old_byte_from_src;
    save_byte_from_array(src.ptr, src.len, &old_byte_from_src);

    /* operation under verification */
    if (aws_byte_buf_write_from_whole_cursor(&buf, src)) {
        sassert(buf.len == buf_old.len + src.len);
        sassert(buf_old.capacity == buf.capacity);
        sassert(buf_old.allocator == buf.allocator);
        if (src.len > 0 && buf.len > 0) {
            assert_bytes_match(buf.buffer + buf_old.len, src.ptr, src.len);
        }
    } else {
        assert_byte_buf_equivalence(&buf, &buf_old, &old_byte_from_buf);
    }

    sassert(aws_byte_buf_is_valid(&buf));
    sassert(aws_byte_cursor_is_valid(&src));
    assert_byte_cursor_equivalence(&src, &src_old, &old_byte_from_src);
    return 0;
}
