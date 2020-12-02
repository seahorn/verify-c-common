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
    if (lhs.ptr == NULL) return 0;
    if (nd_bool()) {
        rhs = lhs;
    } else {
        initialize_byte_cursor(&rhs);
        assume(aws_byte_cursor_is_valid(&rhs));
        if (rhs.ptr == NULL) return 0;
    }

    /* save current state of the data structure */
    struct aws_byte_cursor old_lhs = lhs;
    struct store_byte_from_buffer old_byte_from_lhs;
    save_byte_from_array(lhs.ptr, lhs.len, &old_byte_from_lhs);
    struct aws_byte_cursor old_rhs = rhs;
    struct store_byte_from_buffer old_byte_from_rhs;
    save_byte_from_array(rhs.ptr, rhs.len, &old_byte_from_rhs);

    /* operation under verification */
    if (aws_byte_cursor_compare_lexical(&lhs, &rhs) == 0) {
        sassert(lhs.len == rhs.len);
        if (lhs.len > 0) {
            assert_bytes_match(lhs.ptr, rhs.ptr, lhs.len);
        }
    }
    sassert(aws_byte_cursor_compare_lexical(&lhs, &lhs) == 0);

    /* assertions */
    sassert(aws_byte_cursor_is_valid(&lhs));
    sassert(aws_byte_cursor_is_valid(&rhs));
    if (lhs.len != 0) {
        assert_byte_from_buffer_matches(lhs.ptr, &old_byte_from_lhs);
    }
    if (rhs.len != 0) {
        assert_byte_from_buffer_matches(rhs.ptr, &old_byte_from_rhs);
    }

    return 0;
}
