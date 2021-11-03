/*
 * 
 */

#include <seahorn/seahorn.h>
#include <aws/common/byte_buf.h>
#include <byte_buf_helper.h>
#include <utils.h>

int main() {
    struct aws_byte_buf to;
    initialize_byte_buf(&to);
    assume(aws_byte_buf_is_valid(&to));

    struct aws_byte_cursor from;
    initialize_byte_cursor(&from);
    assume(aws_byte_cursor_is_valid(&from));

    /* save current state of the data structure */
    sea_tracking_on();
    size_t to_old_len = to.len;
    size_t to_old_capacity = to.capacity;

    if (aws_byte_buf_append(&to, &from) == AWS_OP_SUCCESS) {
        sassert(to.len == to_old_len + from.len);
    } else {
        /* if the operation return an error, to must not change */
        sassert(!sea_is_modified((char *)&to));
        sassert(!sea_is_modified((char *)to.buffer));
    }

    sassert(aws_byte_buf_is_valid(&to));
    sassert(aws_byte_cursor_is_valid(&from));
    sassert(!sea_is_modified((char *)to.allocator));
    sassert(to.capacity == to_old_capacity);
    sassert(!sea_is_modified((char *)&from));
    sassert(!sea_is_modified((char *)from.ptr));

    return 0;
}
