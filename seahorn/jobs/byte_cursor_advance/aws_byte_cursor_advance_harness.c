/*
 *
 */

#include <seahorn/seahorn.h>
#include <aws/common/byte_buf.h>
#include <byte_buf_helper.h>
#include <utils.h>

int main() {
    /* data structure */
    struct aws_byte_cursor cursor;
    initialize_byte_cursor(&cursor);
    size_t len = nd_size_t();

    /* assumptions */
    assume(aws_byte_cursor_is_valid(&cursor));

    /* save current state of cursor */
    uint8_t *debug_ptr = cursor.ptr;
    size_t debug_len = cursor.len;
    struct aws_byte_cursor old = cursor;
    struct store_byte_from_buffer old_byte_from_cursor;
    save_byte_from_array(cursor.ptr, cursor.len, &old_byte_from_cursor);

    /* operation under verification */
    struct aws_byte_cursor rv = aws_byte_cursor_advance(&cursor, len);

    /* assertions */
    sassert(aws_byte_cursor_is_valid(&rv));
    if (old.len > (SIZE_MAX >> 1) || len > (SIZE_MAX >> 1) || len > old.len) {
        sassert(rv.ptr == NULL);
        sassert(rv.len == 0);
        if (old.len != 0) {
            assert_byte_from_buffer_matches(cursor.ptr, &old_byte_from_cursor);
        }
    } else {
        sassert(rv.ptr == old.ptr);
        sassert(rv.len == len);
        sassert(cursor.ptr == old.ptr + len);
        sassert(cursor.len == old.len - len);
    }

    return 0;
}
