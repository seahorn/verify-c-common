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
    size_t str_len = 0;
    const char *c_str = can_fail_c_str_allocation(MAX_BUFFER_SIZE, &str_len);

    /* operation under verification */
    struct aws_byte_buf buf = aws_byte_buf_from_c_str(c_str);

    /* assertions */
    sassert(aws_byte_buf_is_valid(&buf));
    sassert(buf.allocator == NULL);
    if (buf.buffer) {
        sassert(buf.len == str_len);
        sassert(buf.capacity == buf.len);
        assert_bytes_match(buf.buffer, (uint8_t *)c_str, buf.len);
    } else {
        if (c_str) {
            sassert(str_len == 0);
        }
        sassert(buf.len == 0);
        sassert(buf.capacity == 0);
    }

    return 0;
}
