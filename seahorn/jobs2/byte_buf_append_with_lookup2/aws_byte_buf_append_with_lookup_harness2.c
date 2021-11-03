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
    assume(aws_byte_buf_is_bounded(&to, MAX_BUFFER_SIZE));
    assume(aws_byte_buf_is_valid(&to));

    struct aws_byte_cursor from;
    initialize_byte_cursor(&from);
    assume(aws_byte_cursor_is_bounded(&from, MAX_BUFFER_SIZE));
    assume(aws_byte_cursor_is_valid(&from));

    /* save current state of the data structure */
    sea_tracking_on();
    size_t to_old_len = to.len;
    size_t to_old_capacity = to.capacity;
    struct aws_byte_cursor from_old = from;

    /**
     * The specification for the function requires that the buffer
     * be at least 256 bytes.
     */
    uint8_t lookup_table[256];
    // This initializes the LUT non-deterministically
    memhavoc(lookup_table, sizeof(lookup_table));

    if (aws_byte_buf_append_with_lookup(&to, &from, lookup_table) == AWS_OP_SUCCESS) {
        sassert(to.len == to_old_len + from.len);
    } else {
        /* if the operation return an error, to must not change */
	sassert(!sea_is_modified((char *)&to));
	sassert(!sea_is_modified((char *)to.buffer));
    }

    sassert(aws_byte_buf_is_valid(&to));
    sassert(aws_byte_cursor_is_valid(&from));
    sassert(!sea_is_modified((char *)to.allocator));
    sassert(to_old_capacity == to.capacity);
    sassert(!sea_is_modified((char *)&from));
    sassert(!sea_is_modified((char *)from.ptr));

    return 0;
}
