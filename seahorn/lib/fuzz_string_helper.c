#include <proof_allocators.h>
#include <seahorn/seahorn.h>
#include <string_helper.h>
#include <assert.h>

/// Allocate a randomly initialized string
const char *ensure_c_str_is_nd_allocated_safe(size_t max_size, size_t *len) {
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
