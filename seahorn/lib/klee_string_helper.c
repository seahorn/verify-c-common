#include <proof_allocators.h>
#include <string_helper.h>
#include <seahorn/seahorn.h>

extern void __assert_fail (const char *__assertion, const char *__file,
			   unsigned int __line, const char *__function);
# define klee_assert(expr)                                            \
  ((expr)                                                             \
   ? (void) (0)                                                       \
   : __assert_fail (#expr, __FILE__, __LINE__, __PRETTY_FUNCTION__))  \

size_t dispatch_alloc_size(size_t sz) {
  switch(sz) {
    case 1: return 1;
    case 2: return 2;
    case 3: return 3;
    case 4: return 4;
    case 5: return 5;
    case 6: return 6;
    case 7: return 7;
    case 8: return 8;
    case 9: return 9;
    case 10: return 10;
    case 11: return 11;
    case 12: return 12;
    case 13: return 13;
    case 14: return 14;
    case 15: return 15;
    case 16: return 16;
    default: return sz <= 4096 ? 4096 : sz; 
  }
}

struct aws_string *ensure_string_is_allocated(size_t len) {
  size_t alloc_size = sizeof(struct aws_string) + len + 1;
  struct aws_string *str = malloc(dispatch_alloc_size(alloc_size));
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

    char *str = malloc(dispatch_alloc_size(alloc_size));
    // make sure allocation is safe
    klee_assert(str != NULL);

    memhavoc(str, alloc_size);

    *len = alloc_size - 1;
    str[*len] = '\0';
    for (size_t j = 0; j < *len; j++) {
        assume(str[j] != '\0');
    }
    return str;
}