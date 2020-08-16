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
    assume(buf.capacity == MAX_BUFFER_SIZE);

    /* operation under verification */
    aws_byte_buf_secure_zero(&buf);

    sassert(aws_byte_buf_is_valid(&buf));
    assert_all_zeroes(buf.buffer, buf.capacity);
    sassert(buf.len == 0);

    return 0;
}
