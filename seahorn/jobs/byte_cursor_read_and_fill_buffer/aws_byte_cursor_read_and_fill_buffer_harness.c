/*
 *
 */

#include <seahorn/seahorn.h>
#include <aws/common/byte_buf.h>
#include <proof_allocators.h>
#include <byte_buf_helper.h>
#include <utils.h>

int main() {
    /* parameters */
    struct aws_byte_cursor cur;
    initialize_byte_cursor(&cur);
    struct aws_byte_buf buf;
    initialize_byte_buf(&buf);

    /* assumptions */
    ensure_byte_cursor_has_allocated_buffer_member(&cur);
    assume(aws_byte_cursor_is_valid(&cur));
    ensure_byte_buf_has_allocated_buffer_member(&buf);
    assume(aws_byte_buf_is_valid(&buf));

    /* save current state of the data structure */
    struct aws_byte_cursor old_cur = cur;
    struct store_byte_from_buffer old_byte_from_cur;
    save_byte_from_array(cur.ptr, cur.len, &old_byte_from_cur);
    struct aws_byte_buf old_buf = buf;
    struct store_byte_from_buffer old_byte_from_buf;
    save_byte_from_array(buf.buffer, buf.len, &old_byte_from_buf);

    /* operation under verification */
    if (aws_byte_cursor_read_and_fill_buffer(&cur, &buf)) {
        sassert(buf.len == buf.capacity);
        assert_bytes_match(old_cur.ptr, buf.buffer, buf.capacity);
    }

    /* assertions */
    sassert(aws_byte_cursor_is_valid(&cur));
    sassert(aws_byte_buf_is_valid(&buf));
    sassert(old_buf.allocator == buf.allocator);
    /* the following assertions are included, because aws_byte_cursor_read internally uses
     * aws_byte_cursor_advance_nospec and it copies the bytes from the advanced cursor to *dest
     */
    if (old_cur.len > (SIZE_MAX >> 1) || old_buf.capacity > (SIZE_MAX >> 1) || old_buf.capacity > old_cur.len) {
        if (old_cur.len != 0) {
            assert_byte_from_buffer_matches(cur.ptr, &old_byte_from_cur);
        }
    } else {
        sassert(cur.ptr == old_cur.ptr + old_buf.capacity);
        sassert(cur.len == old_cur.len - old_buf.capacity);
    }
    return 0;
}
