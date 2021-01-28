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
    uint64_t *dest = can_fail_malloc(sizeof(*dest));

    /* assumptions */
    assume(aws_byte_cursor_is_valid(&cur));
    assume(cur.len >= 8);
    assume(AWS_MEM_IS_READABLE(cur.ptr, 8));
    assume(dest != NULL);

    /* save current state of the data structure */
    struct aws_byte_cursor old_cur = cur;
    struct store_byte_from_buffer old_byte_from_cur;
    save_byte_from_array(cur.ptr, cur.len, &old_byte_from_cur);
    uint64_t dest_copy;
    memcpy(&dest_copy, old_cur.ptr, 8);
    dest_copy = aws_ntoh64(dest_copy);

    /* operation under verification */
    if (aws_byte_cursor_read_be64(&cur, dest)) {
        assert_bytes_match((uint8_t *)&dest_copy, (uint8_t *)dest, 8);
    }

    /* assertions */
    sassert(aws_byte_cursor_is_valid(&cur));
    if (old_cur.len <= (SIZE_MAX >> 1) && 8 <= old_cur.len) {
        /* the following assertions are included, because aws_byte_cursor_read internally uses
         * aws_byte_cursor_advance_nospec and it copies the bytes from the advanced cursor to *dest
         */
        sassert(2 <= old_cur.len && old_cur.len <= (SIZE_MAX >> 1));
        sassert(cur.ptr == old_cur.ptr + 8);
        sassert(cur.len == old_cur.len - 8);
    }
    return 0;
}