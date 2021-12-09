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
    sea_tracking_on();
    sea_reset_modified((char *)&buf);
    sea_reset_modified((char *)buf.buffer);

    /* operation under verification */
    struct aws_byte_cursor cur = aws_byte_cursor_from_buf(&buf);

    /* assertions */
    sassert(aws_byte_buf_is_valid(&buf));
    sassert(aws_byte_cursor_is_valid(&cur));
    sassert(cur.len == buf.len);
    if (cur.ptr) {
        assert_bytes_match(cur.ptr, buf.buffer, buf.len);
    }
    sassert(!sea_is_modified((char *)&buf));
    sassert(!sea_is_modified((char *)buf.buffer));

    return 0;
}
