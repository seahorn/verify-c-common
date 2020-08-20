/*
 * 
 */

#include <seahorn/seahorn.h>
#include <aws/common/byte_buf.h>
#include <byte_buf_helper.h>
#include <utils.h>

int main() {
    /* data structure */
    struct aws_byte_buf buf;
    initialize_byte_buf(&buf);

    /* assumptions */
    assume(aws_byte_buf_is_valid(&buf));

    /* operation under verification */
    aws_byte_buf_clean_up_secure(&buf);

    /* assertions */
    sassert(buf.allocator == NULL);
    sassert(buf.buffer == NULL);
    sassert(buf.len == 0);
    sassert(buf.capacity == 0);

    return 0;
}
