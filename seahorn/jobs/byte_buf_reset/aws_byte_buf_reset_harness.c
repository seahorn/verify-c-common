/*
 * 
 */

#include <seahorn/seahorn.h>
#include <aws/common/byte_buf.h>
#include <byte_buf_helper.h>
#include <utils.h>

int main() {
    struct aws_byte_buf buf;
    initialize_byte_buf(&buf);

    assume(aws_byte_buf_is_valid(&buf));

    struct aws_byte_buf old = buf;
    bool zero_contents = nd_bool();
    aws_byte_buf_reset(&buf, zero_contents);
    sassert(buf.len == 0);
    sassert(buf.allocator == old.allocator);
    sassert(buf.buffer == old.buffer);
    sassert(buf.capacity == old.capacity);
    if (zero_contents) {
        assert_all_bytes_are(buf.buffer, 0, buf.capacity);
    }

    return 0;
}
