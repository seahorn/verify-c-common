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
            ensure_string_is_allocated_nondet_length() : NULL;
    aws_string_destroy(str);

    return 0;
}
