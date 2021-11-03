/*
 * 
 */

#include <seahorn/seahorn.h>
#include <aws/common/byte_buf.h>
#include <byte_buf_helper.h>
#include <utils.h>
#include <proof_allocators.h>

int main() {
    /* parameters */
    struct aws_byte_buf buf;
    initialize_byte_buf(&buf);
    size_t len = nd_size_t();
    assume (len <= MAX_BUFFER_SIZE);
    uint8_t *array = bounded_malloc(MAX_BUFFER_SIZE);

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
    if (aws_byte_buf_write(&buf, array, len)) {
        sassert(buf.len == old_len + len);
        sassert(buf.capacity == old_capacity);
        sassert(!sea_is_modified((char *)buf.allocator));
        if (len > 0 && buf.len > 0) {
            assert_bytes_match(buf.buffer + old_len, array, len);
        }
    } else {
        sassert(!sea_is_modified((char *)&buf));
        sassert(!sea_is_modified((char *)buf.buffer));
    }

    sassert(aws_byte_buf_is_valid(&buf));

    return 0;
}
