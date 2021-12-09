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
    assume(aws_byte_cursor_is_valid(&cur));
    assume(aws_byte_buf_is_valid(&buf));

    /* save current state of the data structure */
    struct aws_byte_cursor old_cur = cur;
    struct aws_byte_buf old_buf = buf;

    sea_tracking_on();
    sea_reset_modified((char *)cur.ptr);
    sea_reset_modified((char *)buf.allocator);

    /* operation under verification */
    if (aws_byte_cursor_read_and_fill_buffer(&cur, &buf)) {
        sassert(buf.len == buf.capacity);
        assert_bytes_match(old_cur.ptr, buf.buffer, buf.capacity);
    }

    /* assertions */
    sassert(aws_byte_cursor_is_valid(&cur));
    sassert(aws_byte_buf_is_valid(&buf));
    sassert(!sea_is_modified((char *)buf.allocator));
    /* the following assertions are included, because aws_byte_cursor_read internally uses
     * aws_byte_cursor_advance_nospec and it copies the bytes from the advanced cursor to *dest
     */
    if (old_cur.len > (SIZE_MAX >> 1) || old_buf.capacity > (SIZE_MAX >> 1) || old_buf.capacity > old_cur.len) {
        if (old_cur.len != 0) {
            sassert(!sea_is_modified((char *)cur.ptr));
        }
    } else {
        sassert(cur.ptr == old_cur.ptr + old_buf.capacity);
        sassert(cur.len == old_cur.len - old_buf.capacity);
    }
    return 0;
}
