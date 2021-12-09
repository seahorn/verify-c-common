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
    sea_tracking_on();
    sea_reset_modified((char *)cur.ptr);
    sea_reset_modified((char *)buf.buffer);

    /* operation under verification */
    if (aws_byte_cursor_eq_byte_buf_ignore_case(&cur, &buf)) {
        sassert(cur.len == buf.len);
    }

    /* assertions */
    sassert(aws_byte_cursor_is_valid(&cur));
    sassert(aws_byte_buf_is_valid(&buf));
    if (cur.len > 0) {
        sassert(!sea_is_modified((char *)cur.ptr));
    }
    sassert(!sea_is_modified((char *)buf.buffer));

    return 0;
}
