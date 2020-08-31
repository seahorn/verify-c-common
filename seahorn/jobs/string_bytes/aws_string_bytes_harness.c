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
    struct aws_string *str = ensure_string_is_allocated_nondet_length();
    //struct aws_string *str = ensure_string_is_allocated_bounded_length(SIZE_MAX - 1 - sizeof(struct aws_string));
    sassert(aws_string_bytes(str) == str->bytes);
    sassert(aws_string_is_valid(str));

    return 0;
}
