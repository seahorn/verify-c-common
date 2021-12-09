/*
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
    size_t length = nd_size_t();
    assume(length <= MAX_BUFFER_SIZE);
    void *dest = bounded_malloc(length);

    /* assumptions */
    assume(aws_byte_cursor_is_valid(&cur));

    /* precondition */
    assume(AWS_MEM_IS_WRITABLE(dest, length));

    /* save current state of the data structure */
    struct aws_byte_cursor old_cur = cur;
    sea_tracking_on();
    sea_reset_modified((char *)cur.ptr);

    /* operation under verification */
    if (aws_byte_cursor_read(&cur, dest, length)) {
        assert_bytes_match(old_cur.ptr, dest, length);
    }

    /* assertions */
    sassert(aws_byte_cursor_is_valid(&cur));
    /* the following assertions are included, because aws_byte_cursor_read internally uses
     * aws_byte_cursor_advance_nospec and it copies the bytes from the advanced cursor to *dest
     */
    if (old_cur.len > (SIZE_MAX >> 1) || length > (SIZE_MAX >> 1) || length > old_cur.len) {
        if (old_cur.len != 0) {
            sassert(!sea_is_modified((char *)cur.ptr));
        }
    } else {
        sassert(cur.ptr == old_cur.ptr + length);
        sassert(cur.len == old_cur.len - length);
    }
    return 0;
}
