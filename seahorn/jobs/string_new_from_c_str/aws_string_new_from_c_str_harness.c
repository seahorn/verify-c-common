/*
 *
 */

#include <aws/common/string.h>
#include <seahorn/seahorn.h>
#include <byte_buf_helper.h>
#include <string_helper.h>
#include <utils.h>
#include <stddef.h>
#include <proof_allocators.h>

int main() {
    /* parameters */
    const char *c_str = ensure_c_str_is_allocated(MAX_STRING_LEN);
    struct aws_allocator *allocator = _allocator();

    /* operation under verification */
    struct aws_string *str = aws_string_new_from_c_str(allocator, c_str);

    /* assertions */
    if (str) {
        sassert(str->len <= MAX_STRING_LEN);
        sassert(str->bytes[str->len] == 0);
        assert_bytes_match(str->bytes, (uint8_t*)c_str, str->len);
        sassert(aws_string_is_valid(str));
    }
    sassert(aws_c_string_is_valid(c_str));

    return 0;
}
