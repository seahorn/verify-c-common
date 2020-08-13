/*
 * 
 */

#include <seahorn/seahorn.h>
#include <aws/common/string.h>
#include <aws/common/byte_buf.h>
#include <byte_buf_helper.h>
#include <string_helper.h>
#include <utils.h>
#include <stddef.h>

int main() {
    struct aws_string *str = nd_bool() ? ensure_string_is_allocated_bounded_length(MAX_STRING_LEN) : NULL;
    struct aws_byte_buf buf;
    initialize_byte_buf(&buf);

    assume(aws_byte_buf_is_valid(&buf));

    /* save current state of the data structure */
    struct aws_byte_buf old_buf = buf;
    struct store_byte_from_buffer old_byte_from_buf;
    save_byte_from_array(buf.buffer, buf.len, &old_byte_from_buf);

    size_t available_cap = buf.capacity - buf.len;
    bool nondet_parameter = nd_bool();

    if (aws_byte_buf_write_from_whole_string(nondet_parameter ? &buf : NULL, str) && str) {
        sassert(aws_string_is_valid(str));
        sassert(available_cap >= str->len);
        if (nondet_parameter) {
            sassert(buf.len == old_buf.len + str->len);
            sassert(old_buf.capacity == buf.capacity);
            sassert(old_buf.allocator == buf.allocator);
            if (str->len > 0 && buf.len > 0) {
                assert_bytes_match(buf.buffer + old_buf.len, str->bytes, str->len);
            }
        }
    } else {
        assert_byte_buf_equivalence(&buf, &old_buf, &old_byte_from_buf);
    }

    sassert(aws_byte_buf_is_valid(&buf));

    return 0;
}
