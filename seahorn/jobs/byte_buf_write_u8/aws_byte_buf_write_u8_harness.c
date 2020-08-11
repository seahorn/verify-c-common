/*
 * 
 */

#include <seahorn/seahorn.h>
#include <aws/common/byte_buf.h>
#include <byte_buf_helper.h>
#include <utils.h>

int main() {
    /* parameters */
    struct aws_byte_buf buf;
    initialize_byte_buf(&buf);
    uint8_t x = nd_uint8_t();

    /* assumptions */
    assume(aws_byte_buf_is_valid(&buf));

    /* save current state of the parameters */
    struct aws_byte_buf old = buf;
    struct store_byte_from_buffer old_byte_from_buf;
    save_byte_from_array(buf.buffer, buf.len, &old_byte_from_buf);

    /* operation under verification */
    if (aws_byte_buf_write_u8(&buf, x)) {
        sassert(buf.len == old.len + 1);
        sassert(old.capacity == buf.capacity);
        sassert(old.allocator == buf.allocator);
    } else {
        assert_byte_buf_equivalence(&buf, &old, &old_byte_from_buf);
    }

    sassert(aws_byte_buf_is_valid(&buf));
}
