#include <proof_allocators.h>
#include <seahorn/seahorn.h>
#include <string_helper.h>
#include <assert.h>

struct aws_string *ensure_string_is_allocated(size_t len) {
  struct aws_string *str = malloc(sizeof(struct aws_string) + len + 1);
  memhavoc(str, sizeof(struct aws_string) + len);

  if (str) {
    /* Fields are declared const, so we need to copy them in like this */
    *(struct aws_allocator **)(&str->allocator) =
        nd_bool() ? sea_allocator() : NULL;
    *(size_t *)(&str->len) = len;
    *(uint8_t *)&str->bytes[len] = '\0';
  }
  return str;
}

struct aws_string *ensure_string_is_allocated_bounded_length(size_t max_size) {
  size_t len = nd_size_t();
  // len < max_size
  len %= max_size;
  return ensure_string_is_allocated(len);
}

static const char *_ensure_c_str_is_nd_allocated(size_t max_size, size_t *len,
                                                 bool safe) {
  bool should_fail = nd_bool();
  if (!safe && should_fail) {
    return NULL;
  }
  size_t alloc_size;
  alloc_size = nd_size_t();

  // 1 <= alloc_size <= max_size + 1
  alloc_size %= max_size;
  ++alloc_size;

  char *str = malloc(alloc_size);
  // safe allocation
  assert(str);

  *len = alloc_size - 1;
  // -- zero terminated
  str[*len] = '\0';
  // -- initialized
  memhavoc(str, *len);

  // -- remove any spurious 1
  for (unsigned i = 0; i < *len; ++i) {
    if (str[i] == 0) str[i] = 1;
  }

  return str;
}

/// Allocate a randomly initialized string
const char *ensure_c_str_is_nd_allocated_safe(size_t max_size, size_t *len) {
  return _ensure_c_str_is_nd_allocated(max_size, len, true);
}

const char *ensure_c_str_is_nd_allocated(size_t max_size, size_t *len) {
  return _ensure_c_str_is_nd_allocated(max_size, len, false);
}

bool aws_byte_buf_has_allocator(const struct aws_byte_buf *const buf) {
  return (buf->allocator == sea_allocator());
}
