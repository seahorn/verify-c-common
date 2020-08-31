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
    struct aws_string *str_a = nd_bool() ?
            ensure_string_is_allocated_bounded_length(MAX_STRING_LEN) :
            NULL;
    struct aws_string *str_b = nd_bool() ?
            (nd_bool() ? str_a : NULL) :
            ensure_string_is_allocated_bounded_length(MAX_STRING_LEN);
    if (aws_string_eq_ignore_case(str_a, str_b) && str_a && str_b) {
        sassert(aws_string_is_valid(str_a));
        sassert(aws_string_is_valid(str_b));
        sassert(str_a->len == str_b->len);
    }

    return 0;
}
