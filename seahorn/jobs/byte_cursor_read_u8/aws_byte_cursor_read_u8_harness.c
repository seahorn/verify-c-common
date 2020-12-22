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
    assume(length >= 1);
    uint8_t *dest = bounded_malloc(length);

    /* assumptions */
    assume(aws_byte_cursor_is_valid(&cur));

    /* precondition */
    assume(AWS_MEM_IS_WRITABLE(dest, 1));

    /* save current state of the data structure */
    struct aws_byte_cursor old_cur = cur;
    struct store_byte_from_buffer old_byte_from_cur;
    save_byte_from_array(cur.ptr, cur.len, &old_byte_from_cur);

    /* operation under verification */
    if (aws_byte_cursor_read_u8(&cur, dest)) {
        assert_bytes_match(old_cur.ptr, dest, 1);
    }

    /* assertions */
    sassert(aws_byte_cursor_is_valid(&cur));
    /* the following assertions are included, because aws_byte_cursor_read internally uses
     * aws_byte_cursor_advance_nospec and it copies the bytes from the advanced cursor to *dest
     */
    if (old_cur.len < (SIZE_MAX >> 1) && old_cur.len > 1) {
        sassert(cur.ptr == old_cur.ptr + 1);
        sassert(cur.len == old_cur.len - 1);
    }
}
