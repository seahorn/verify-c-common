/*
 *
 */

#include <seahorn/seahorn.h>
#include <aws/common/byte_buf.h>
#include <byte_buf_helper.h>
#include <utils.h>
#include <proof_allocators.h>

int main() {
    /* parameter */
    size_t str_len;
    const char *c_str = ensure_c_str_is_nd_allocated(MAX_BUFFER_SIZE, &str_len);

    /* operation under verification */
    struct aws_byte_cursor cur = aws_byte_cursor_from_c_str(c_str);

    /* assertions */
    sassert(aws_byte_cursor_is_valid(&cur));
    if (cur.ptr) { /* if ptr is NULL len shoud be 0, otherwise equal to c_str */
        sassert(cur.len == str_len);
        assert_bytes_match(cur.ptr, (uint8_t *)c_str, cur.len);
    } else {
        sassert(cur.len == 0);
    }

    return 0;
}
