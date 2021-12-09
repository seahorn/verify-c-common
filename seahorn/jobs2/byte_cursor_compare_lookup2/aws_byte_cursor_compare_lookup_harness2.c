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
    /**
     * The specification for the function requires that the buffer
     * be at least 256 bytes.
     */
    uint8_t lookup_table[256];
    // This initializes the LUT non-deterministically
    memhavoc(lookup_table, sizeof(lookup_table));

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
    if (aws_byte_cursor_compare_lookup(&lhs, &rhs, lookup_table) == 0) {
        sassert(lhs.len == rhs.len);
    }
    sassert(aws_byte_cursor_compare_lookup(&lhs, &lhs, lookup_table) == 0);

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
