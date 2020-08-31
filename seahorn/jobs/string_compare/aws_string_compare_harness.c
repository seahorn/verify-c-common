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
    bool nondet_parameter = nd_bool();
    if (aws_string_compare(str_a, nondet_parameter ? str_b : str_a) == AWS_OP_SUCCESS) {
        if (nondet_parameter && str_a && str_b) {
            assert_bytes_match(str_a->bytes, str_b->bytes, str_a->len);
        }
    }
    if (str_a) {
        sassert(aws_string_is_valid(str_a));
    }
    if (str_b) {
        sassert(aws_string_is_valid(str_b));
    }

    return 0;
}
