/*
 *
 */

#include <aws/common/string.h>
#include <seahorn/seahorn.h>
#include <byte_buf_helper.h>
#include <string_helper.h>
#include <utils.h>

int main() {
    struct aws_string *str = ensure_string_is_allocated_bounded_length(MAX_STRING_LEN);
    struct aws_byte_cursor cursor = aws_byte_cursor_from_string(str);
    sassert(aws_string_is_valid(str));
    sassert(aws_byte_cursor_is_valid(&cursor));
    sassert(cursor.len == str->len);
    sassert(cursor.ptr == str->bytes);
    assert_bytes_match(str->bytes, cursor.ptr, str->len);

    return 0;
}
