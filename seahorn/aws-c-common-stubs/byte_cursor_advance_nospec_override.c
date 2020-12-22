
#include <aws/common/byte_buf.h>
#include <aws/common/private/byte_buf.h>

/**
 * Behaves identically to aws_byte_cursor_advance, but avoids speculative
 * execution potentially reading out-of-bounds pointers (by returning an
 * empty ptr in such speculated paths).
 *
 * This should generally be done when using an untrusted or
 * data-dependent value for 'len', to avoid speculating into a path where
 * cursor->ptr points outside the true ptr length.
 */

struct aws_byte_cursor aws_byte_cursor_advance_nospec(struct aws_byte_cursor *const cursor, size_t len) {
    AWS_PRECONDITION(aws_byte_cursor_is_valid(cursor));

    struct aws_byte_cursor rv;

    if (len <= cursor->len && len <= (SIZE_MAX >> 1) && cursor->len <= (SIZE_MAX >> 1)) {
        /*
         * If we're speculating past a failed bounds check, null out the pointer. This ensures
         * that we don't try to read past the end of the buffer and leak information about other
         * memory through timing side-channels.
         */
        uintptr_t mask = aws_nospec_mask(len, cursor->len + 1);

        /* Make sure we don't speculate-underflow len either */
        len = len & mask;
        // mask is 0 if speculating past a failed bounds check. Otherwise, returns UINTPTR_MAX
        cursor->ptr = mask ? cursor->ptr : NULL;
        /* Make sure subsequent nospec accesses don't advance ptr past NULL */
        cursor->len = cursor->len & mask;

        rv.ptr = cursor->ptr;
        /* Make sure anything acting upon the returned cursor _also_ doesn't advance past NULL */
        rv.len = len & mask;

        cursor->ptr += len;
        cursor->len -= len;
    } else {
        rv.ptr = NULL;
        rv.len = 0;
    }

    AWS_POSTCONDITION(aws_byte_cursor_is_valid(cursor));
    AWS_POSTCONDITION(aws_byte_cursor_is_valid(&rv));
    return rv;
}