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
    uint64_t x = nd_uint64_t();

    /* assumptions */
    assume(aws_byte_buf_is_valid(&buf));

    /* save current state of the parameters */
    struct aws_byte_buf old = buf;
    struct store_byte_from_buffer old_byte_from_buf;
    save_byte_from_array(buf.buffer, buf.len, &old_byte_from_buf);

    size_t old_len = buf.len;
    size_t old_capacity = buf.capacity;
    sea_tracking_on();

    /* operation under verification */
    if (aws_byte_buf_write_be64(&buf, x)) {
        sassert(buf.len == old_len + 8);
        sassert(old_capacity == buf.capacity);
        sassert(!sea_is_modified((char *)buf.allocator));
    } else {
        sassert(!sea_is_modified((char *)&buf));
        sassert(!sea_is_modified((char *)buf.buffer));
    }

    sassert(aws_byte_buf_is_valid(&buf));

    return 0;
}
