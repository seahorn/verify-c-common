/*
 *
 */

#include <seahorn/seahorn.h>
#include <aws/common/byte_buf.h>
#include <byte_buf_helper.h>
#include <utils.h>

int main() {
    /* parameters */
    struct aws_byte_cursor lhs;
    initialize_byte_cursor(&lhs);
    struct aws_byte_cursor rhs;

    /* assumptions */
    assume(aws_byte_cursor_is_valid(&lhs));
    if (nd_bool()) {
        rhs = lhs;
    } else {
        initialize_byte_cursor(&rhs);
        assume(aws_byte_cursor_is_valid(&rhs));
    }

    /* save current state of the data structure */
    sea_tracking_on();
    sea_reset_modified((char *)lhs.ptr);
    sea_reset_modified((char *)rhs.ptr);

    /* operation under verification */
    if (aws_byte_cursor_eq_ignore_case(&lhs, &rhs)) {
        sassert(lhs.len == rhs.len);
    }

    /* assertions */
    sassert(aws_byte_cursor_is_valid(&lhs));
    sassert(aws_byte_cursor_is_valid(&rhs));
    if (lhs.len != 0) {
        sassert(!sea_is_modified((char *)lhs.ptr));
    }
    if (rhs.len != 0) {
        sassert(!sea_is_modified((char *)rhs.ptr));
    }

    return 0;
}
