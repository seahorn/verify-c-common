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
    size_t requested_capacity = MAX_BUFFER_SIZE;
    if (buf.capacity < MAX_BUFFER_SIZE) {
        int rval = aws_byte_buf_reserve_relative(&buf, requested_capacity);

        if (rval == AWS_OP_SUCCESS) {
            sassert(buf.capacity >= (old.len + requested_capacity));
            sassert(aws_byte_buf_has_allocator(&buf));
        }
        sassert(aws_byte_buf_is_valid(&buf));
    }

    return 0;
}
