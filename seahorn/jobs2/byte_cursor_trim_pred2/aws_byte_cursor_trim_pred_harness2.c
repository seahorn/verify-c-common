/**
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

    /* assumptions */
    assume(aws_byte_cursor_is_bounded(&cur, MAX_BUFFER_SIZE));
    assume(aws_byte_cursor_is_valid(&cur));

    /* save current state of the data structure */
    sea_tracking_on();
    sea_reset_modified((char *)cur.ptr);

    /* operation under verification */
    struct aws_byte_cursor rv = aws_byte_cursor_trim_pred(&cur, uninterpreted_predicate_fn);

    /* assertions */
    sassert(aws_byte_cursor_is_valid(&cur));
    sassert(aws_byte_cursor_is_valid(&rv));
    if (cur.len > 0) {
        sassert(!sea_is_modified((char *)cur.ptr));
    }
    return 0;
}