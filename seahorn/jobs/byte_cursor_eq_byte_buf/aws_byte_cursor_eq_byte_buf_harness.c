/*
 * 
 */

#include <seahorn/seahorn.h>
#include <aws/common/byte_buf.h>
#include <byte_buf_helper.h>
#include <utils.h>

int main() {
    /* parameters */
    struct aws_byte_cursor cur;
    initialize_byte_cursor(&cur);
    struct aws_byte_buf buf;
    initialize_byte_buf(&buf);

    /* assumptions */
    assume(aws_byte_cursor_is_valid(&cur));
    assume(aws_byte_buf_is_valid(&buf));

    /* save current state of the data structure */
    struct store_byte_from_buffer old_byte_from_cur;
    save_byte_from_array(cur.ptr, cur.len, &old_byte_from_cur);
    struct aws_byte_buf old_buf = buf;
    struct store_byte_from_buffer old_byte_from_buf;
    save_byte_from_array(buf.buffer, buf.len, &old_byte_from_buf);

    /* operation under verification */
    if (aws_byte_cursor_eq_byte_buf(&cur, &buf)) {
        sassert(cur.len == buf.len);
        if (cur.len > 0) {
            assert_bytes_match(cur.ptr, buf.buffer, cur.len);
        }
    }

    /* assertions */
    sassert(aws_byte_cursor_is_valid(&cur));
    sassert(aws_byte_buf_is_valid(&buf));
    if (cur.len > 0) {
        assert_byte_from_buffer_matches(cur.ptr, &old_byte_from_cur);
    }
    assert_byte_buf_equivalence(&buf, &old_buf, &old_byte_from_buf);

    return 0;
}
