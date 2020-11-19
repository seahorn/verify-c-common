#include <proof_allocators.h>
#include <string_helper.h>
#include <seahorn/seahorn.h>

struct aws_string *ensure_string_is_allocated(size_t len) {
  size_t alloc_size = sizeof(struct aws_string) + len + 1;
  struct aws_string *str = bounded_malloc(alloc_size);
  memhavoc(str, alloc_size);

  if (str) {
    /* Fields are declared const, so we need to copy them in like this */
    *(struct aws_allocator **)(&str->allocator) = nd_bool() ? sea_allocator() : NULL;
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

/** Allocate a randomly initialized string with a range of maximal length
 */
const char *ensure_c_str_is_nd_allocated_safe(size_t max_size, size_t *len) {
    size_t alloc_size;
    alloc_size = nd_size_t();
    // allocate size (0, max_size]
    assume(alloc_size > 0);
    assume(alloc_size <= max_size);

    char *str = bounded_malloc(alloc_size);
    // make sure allocation is safe
    assume(str != NULL);

    memhavoc(str, alloc_size);

    *len = alloc_size - 1;
    str[*len] = '\0';
    for (size_t j = 0; j < *len; j++) {
        assume(str[j] != '\0');
    }
    return str;
}