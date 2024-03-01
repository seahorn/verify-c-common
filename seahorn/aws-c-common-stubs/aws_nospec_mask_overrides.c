#include <stdint.h>
#include <stddef.h>

/**
 * FUNCTION: aws_nospec_mask
 *
 * This function overrides the original implementation of the
 * aws_nospec_mask function from byte_buf.h with a simplified version.
 *
 * We follow the specs on the comments below to filter out the checks without
 * performing bitwise operations.
 * FIXME: now something wrong on the BMC part
 */

/**
 * If index >= bound, bound > (SIZE_MAX / 2), or index > (SIZE_MAX / 2), returns
 * 0. Otherwise, returns UINTPTR_MAX.  This function is designed to return the correct
 * value even under CPU speculation conditions, and is intended to be used for
 * SPECTRE mitigation purposes.
 */
size_t aws_nospec_mask(size_t index, size_t bound) {
    /*
     * SPECTRE mitigation - we compute a mask that will be zero if len < 0
     * or len >= buf->len, and all-ones otherwise, and AND it into the index.
     * It is critical that we avoid any branches in this logic.
     */

    /*
     * Hide the index value from the optimizer. This helps ensure that all this
     * logic doesn't get eliminated.
     */
#if defined(__GNUC__) || defined(__clang__)
    __asm__ __volatile__("" : "+r"(index));
#endif
#if defined(_MSVC_LANG)
    /*
     * MSVC doesn't have a good way for us to blind the optimizer, and doesn't
     * even have inline asm on x64. Some experimentation indicates that this
     * hack seems to confuse it sufficiently for our needs.
     */
    *((volatile uint8_t *)&index) += 0;
#endif

    if (index >= bound || bound > (SIZE_MAX / 2) || index > (SIZE_MAX / 2)) {
      return 0;
    }

    return UINTPTR_MAX;
}