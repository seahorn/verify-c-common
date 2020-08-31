/*
 *
 */

#include <aws/common/string.h>
#include <seahorn/seahorn.h>
#include <byte_buf_helper.h>
#include <string_helper.h>
#include <utils.h>
#include <stddef.h>

int main() {
    struct aws_string *str = nd_bool() ?
            ensure_string_is_allocated_bounded_length(MAX_STRING_LEN) :
            NULL;
    struct aws_byte_cursor cursor;
    initialize_byte_cursor(&cursor);

    assume(aws_byte_cursor_is_valid(&cursor));

    bool nondet_parameter = nd_bool();
    if (aws_string_eq_byte_cursor(str, nondet_parameter ? &cursor : NULL) && str) {
        sassert(aws_string_is_valid(str));
        if (nondet_parameter) {
            sassert(str->len == cursor.len);
            if (str->len > 0) {
                assert_bytes_match(str->bytes, cursor.ptr, str->len);
            }
        }
    }
    sassert(aws_byte_cursor_is_valid(&cursor));

    return 0;
}
