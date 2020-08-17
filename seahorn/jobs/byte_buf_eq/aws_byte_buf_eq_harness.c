/*
 * 
 */

#include <seahorn/seahorn.h>
#include <aws/common/byte_buf.h>
#include <byte_buf_helper.h>
#include <utils.h>

int main() {
    /* parameters */
    struct aws_byte_buf lhs;
    initialize_byte_buf(&lhs);
    struct aws_byte_buf rhs;
    initialize_byte_buf(&rhs);

    /* assumptions */
    assume(aws_byte_buf_is_valid(&lhs));
    if (nd_bool()) {
        rhs = lhs;
    } else {
        assume(aws_byte_buf_is_valid(&rhs));
    }

    /* save current state of the data structure */
    struct aws_byte_buf old_lhs = lhs;
    struct store_byte_from_buffer old_byte_from_lhs;
    save_byte_from_array(lhs.buffer, lhs.len, &old_byte_from_lhs);
    struct aws_byte_buf old_rhs = rhs;
    struct store_byte_from_buffer old_byte_from_rhs;
    save_byte_from_array(rhs.buffer, rhs.len, &old_byte_from_rhs);

    /* operation under verification */
    if (aws_byte_buf_eq(&lhs, &rhs)) {
        sassert(lhs.len == rhs.len);
        if (lhs.len > 0) {
            assert_bytes_match(lhs.buffer, rhs.buffer, lhs.len);
        }
    }

    /* assertions */
    sassert(aws_byte_buf_is_valid(&lhs));
    sassert(aws_byte_buf_is_valid(&rhs));
    assert_byte_buf_equivalence(&lhs, &old_lhs, &old_byte_from_lhs);
    assert_byte_buf_equivalence(&rhs, &old_rhs, &old_byte_from_rhs);

    return 0;
}
