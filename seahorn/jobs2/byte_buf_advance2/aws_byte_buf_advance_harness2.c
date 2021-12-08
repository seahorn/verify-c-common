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
    struct aws_byte_buf output;
    size_t len = nd_size_t();

    /* assumptions */
    assume(aws_byte_buf_is_valid(&buf));
    if (nd_bool()) {
        output = buf;
    } else {
        initialize_byte_buf(&output);
        assume(aws_byte_buf_is_valid(&output));
    }

    /* save current state of the parameters */
    sea_tracking_on();
    size_t old_len = buf.len;
    size_t old_capacity = buf.capacity;

    /* operation under verification */
    if (aws_byte_buf_advance(&buf, &output, len)) {
        sassert(buf.len == old_len + len);

        sassert(buf.capacity == old_capacity);

        if (old_len > 0) {
            sassert(!sea_is_modified((char *)buf.buffer));
        }
        sassert(output.len == 0);
        sassert(output.capacity == len);
        sassert(output.allocator == NULL);
    } else {
        sassert(!sea_is_modified((char *)&buf));
        sassert(!sea_is_modified((char *)buf.buffer));

        sassert(output.len == 0);
        sassert(output.capacity == 0);
        sassert(output.allocator == NULL);
        sassert(output.buffer == NULL);
    }
    sassert(aws_byte_buf_is_valid(&buf));
    sassert(aws_byte_buf_is_valid(&output));
    sassert(!sea_is_modified((char *)buf.allocator));

    return 0;
}
