/**
 */

#include "nondet.h"
#include <seahorn/seahorn.h>
#include <aws/common/byte_buf.h>
#include <proof_allocators.h>
#include <utils.h>

int main() {
    /* assumptions */
    size_t lhs_len = nd_size_t();
    assume(lhs_len <= MAX_BUFFER_SIZE);
    void *lhs = can_fail_malloc_havoc(lhs_len);

    #ifdef __KLEE__
        // The program path for a failed case which 
        // lhs = NULL & lhs_len != 0 should be ignored.
        if (!lhs && lhs_len != 0) return 0;
    #endif

    void *rhs;
    size_t rhs_len = nd_size_t();
    if (nd_bool()) { /* rhs could be equal to lhs */
        rhs_len = lhs_len;
        rhs = lhs;
    } else {
        assume(rhs_len <= MAX_BUFFER_SIZE);
        rhs = can_fail_malloc_havoc(rhs_len);
    }

    #ifdef __KLEE__
        // The program path for a failed case which 
        // rhs = NULL & rhs_len != 0 should be ignored.
        if (!rhs && rhs_len != 0) return 0;
    #endif

    /* save current state of the parameters */
    struct store_byte_from_buffer old_byte_from_lhs;
    save_byte_from_array((uint8_t *)lhs, lhs_len, &old_byte_from_lhs);
    struct store_byte_from_buffer old_byte_from_rhs;
    save_byte_from_array((uint8_t *)rhs, rhs_len, &old_byte_from_rhs);

    /* pre-conditions */
    assume((lhs_len == 0) || AWS_MEM_IS_READABLE(lhs, lhs_len));
    assume((rhs_len == 0) || AWS_MEM_IS_READABLE(rhs, rhs_len));

    /* operation under verification */
    if (aws_array_eq(lhs, lhs_len, rhs, rhs_len)) {
        /* asserts equivalence */
        sassert(lhs_len == rhs_len);
        if (lhs_len > 0 && lhs) {
            assert_bytes_match((uint8_t *)lhs, (uint8_t *)rhs, lhs_len);
        }
    }

    /* asserts both parameters remain unchanged */
    if (lhs_len > 0 && lhs) {
        assert_byte_from_buffer_matches((uint8_t *)lhs, &old_byte_from_lhs);
    }
    if (rhs_len > 0 && rhs) {
        assert_byte_from_buffer_matches((uint8_t *)rhs, &old_byte_from_rhs);
    }
}
