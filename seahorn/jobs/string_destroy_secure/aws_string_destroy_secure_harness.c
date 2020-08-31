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
    struct aws_string *str = ensure_string_is_allocated_bounded_length(MAX_STRING_LEN);
    char const *bytes = str->bytes;
    size_t len = str->len;
    /* Tell CBMC to keep the buffer live after the free */
    __CPROVER_allocated_memory(bytes, len);
    bool nondet_parameter = nd_bool();
    aws_string_destroy_secure(nondet_parameter ? str : NULL);
    if (nondet_parameter) {
        assert_all_zeroes(bytes, len);
    }

    return 0;
}
