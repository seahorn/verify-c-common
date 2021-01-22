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
    size_t alloc_size = nd_size_t();
    KLEE_ASSUME(alloc_size < MAX_STRING_LEN);
    uint8_t *array = bounded_malloc(alloc_size);
    struct aws_allocator *allocator = sea_allocator();
    size_t reported_size = nd_size_t();

    /* precondition */
    assume(reported_size <= alloc_size);

    /* operation under verification */
    struct aws_string *str = aws_string_new_from_array(allocator, array, reported_size);

    /* assertions */
    if (str) {
        sassert(str->len == reported_size);
        sassert(str->bytes[str->len] == 0);
        assert_bytes_match(str->bytes, array, str->len);
        sassert(aws_string_is_valid(str));
    }

    return 0;
}
