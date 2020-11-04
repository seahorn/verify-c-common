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
    struct aws_string *source = ensure_string_is_allocated_bounded_length(SIZE_MAX - 1 - sizeof(struct aws_string));
    struct aws_allocator *allocator =
            (source->allocator) ? source->allocator : sea_allocator();

    /* operation under verification */
    struct aws_string *str = aws_string_new_from_string(allocator, source);

    /* assertions */
    if (str) {
        sassert(source->len == str->len);
        sassert(str->allocator == allocator);
        sassert(str->bytes[str->len] == '\0');
        assert_bytes_match(source->bytes, str->bytes, source->len);
        sassert(aws_string_is_valid(str));
    }
    sassert(aws_string_is_valid(source));

    return 0;
}
