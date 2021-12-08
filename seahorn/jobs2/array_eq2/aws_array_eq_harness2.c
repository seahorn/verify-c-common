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

    /* pre-conditions */
    assume((lhs_len == 0) || AWS_MEM_IS_READABLE(lhs, lhs_len));
    assume((rhs_len == 0) || AWS_MEM_IS_READABLE(rhs, rhs_len));

    /* save current state of the parameters */
    sea_tracking_on();

    /* operation under verification */
    if (aws_array_eq(lhs, lhs_len, rhs, rhs_len)) {
        /* asserts equivalence */
        sassert(lhs_len == rhs_len);
        if (lhs_len > 0 && lhs) {
            assert_bytes_match((uint8_t *)lhs, (uint8_t *)rhs, lhs_len);
        }
    }

    /* asserts both parameters remain unchanged */
    sassert(!sea_is_modified((char *)lhs));
    sassert(!sea_is_modified((char *)rhs)); 
}
