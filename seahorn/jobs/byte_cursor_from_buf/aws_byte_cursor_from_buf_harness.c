/*
 *
 */

#include <seahorn/seahorn.h>
#include <aws/common/byte_buf.h>
#include <byte_buf_helper.h>
#include <utils.h>
#include <proof_allocators.h>

int main() {
    /* parameter */
    struct aws_byte_buf buf;
    initialize_byte_buf(&buf);

    /* assumptions */
    assume(aws_byte_buf_is_valid(&buf));

    /* save current state of the parameters */
    struct aws_byte_buf old = buf;
    struct store_byte_from_buffer old_byte_from_buf;
    save_byte_from_array(buf.buffer, buf.len, &old_byte_from_buf);

    /* operation under verification */
    struct aws_byte_cursor cur = aws_byte_cursor_from_buf(&buf);

    /* assertions */
    sassert(aws_byte_buf_is_valid(&buf));
    sassert(aws_byte_cursor_is_valid(&cur));
    assert_byte_buf_equivalence(&buf, &old, &old_byte_from_buf);
    sassert(cur.len == buf.len);
    if (cur.ptr) {
        assert_bytes_match(cur.ptr, buf.buffer, buf.len);
    }

    return 0;
}
