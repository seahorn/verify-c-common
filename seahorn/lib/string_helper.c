#include <seahorn/seahorn.h>
#include <string_helper.h>
#include <proof_allocators.h>

struct aws_string *ensure_string_is_allocated(size_t len) {
    struct aws_string *str = bounded_malloc(sizeof(struct aws_string) + len + 1);

    if (str) {
      /* Fields are declared const, so we need to copy them in like this */
      *(struct aws_allocator **)(&str->allocator) =
          nd_bool() ? nd_voidp() : NULL;
      *(size_t *)(&str->len) = len;
      *(uint8_t *)&str->bytes[len] = '\0';
    }
    return str;
}

struct aws_string *ensure_string_is_allocated_bounded_length(size_t max_size) {
    size_t len = nd_size_t();
    assume(len < max_size);
    return ensure_string_is_allocated(len);
}

struct aws_string *ensure_string_is_allocated_nondet_length(void) {
    /* Considers any size up to the maximum possible size for the array [bytes] in aws_string */
    return ensure_string_is_allocated_bounded_length(SIZE_MAX - 1 - sizeof(struct aws_string));
}
