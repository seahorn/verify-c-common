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
            ensure_string_is_allocated_bounded_length(MAX_STRING_LEN /*  max size */) :
            NULL;
    const char *c_str = nd_bool() ?
            ensure_c_str_is_allocated(MAX_STRING_LEN) :
            NULL;
    if (aws_string_eq_c_str_ignore_case(str, c_str) && str && c_str) {
        sassert(aws_string_is_valid(str));
        sassert(aws_c_string_is_valid(c_str));
        sassert(str->len == strlen(c_str));
    }

    return 0;
}
