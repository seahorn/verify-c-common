/*
 *
 */

#include <seahorn/seahorn.h>
#include <aws/common/byte_buf.h>
#include <proof_allocators.h>
#include <byte_buf_helper.h>
#include <utils.h>
void assert_bytes_match_test(const uint16_t *const a, const uint16_t *const b,
                        const size_t len) {
  sassert(len == 0 || !a == !b);
  if (len > 0 && a != NULL && b != NULL) {
    size_t i = nd_size_t();
    /* prevent spurious pointer overflows */
    assume(i < len && len < MAX_MALLOC);
    sassert(a[i] == b[i]);
  }
}

int main() {
    /* parameters */
    struct aws_byte_cursor cur;
    initialize_byte_cursor(&cur);
    uint16_t *dest = can_fail_malloc(sizeof(*dest));
    uint16_t *src = can_fail_malloc(sizeof(*src));

    /* assumptions */
    ensure_byte_cursor_has_allocated_buffer_member(&cur);
    assume(aws_byte_cursor_is_valid(&cur));
    assume(cur.len >= 2);
    assume(AWS_MEM_IS_READABLE(cur.ptr, 2));
    assume(dest != NULL);
    assume(src != NULL);

    /* save current state of the data structure */
    struct aws_byte_cursor old_cur = cur;
    struct store_byte_from_buffer old_byte_from_cur;
    save_byte_from_array(cur.ptr, cur.len, &old_byte_from_cur);
    uint16_t dest_copy = nd_uint16_t();
    memcpy(&dest_copy, old_cur.ptr, 2);
    dest_copy = aws_ntoh16(dest_copy);

    memcpy(dest, old_cur.ptr, 2);
    *dest = aws_ntoh16(*dest);
    memcpy(src, cur.ptr, 2);
    assert_bytes_match_test(src, dest, 2);

    return 0;

    /* operation under verification */
    if (aws_byte_cursor_read_be16(&cur, dest)) {
        assert_bytes_match_test(&dest_copy, dest, 2);
        /* the following assertions are included, because aws_byte_cursor_read internally uses
         * aws_byte_cursor_advance_nospec and it copies the bytes from the advanced cursor to *dest
         */
        sassert(2 <= old_cur.len && old_cur.len <= (SIZE_MAX >> 1));
        sassert(cur.ptr == old_cur.ptr + 2);
        sassert(cur.len == old_cur.len - 2);
    } else {
        sassert(cur.len == old_cur.len);
        if (cur.len != 0) {
            assert_byte_from_buffer_matches(cur.ptr, &old_byte_from_cur);
        }
    }

    /* assertions */
    sassert(aws_byte_cursor_is_valid(&cur));
}
