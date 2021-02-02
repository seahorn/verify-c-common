#include <bounds.h>
#include <proof_allocators.h>
#include <string_helper.h>
#include <sea_allocators.h>
#include <seahorn/seahorn.h>

struct aws_string *ensure_string_is_allocated(size_t len) {
  size_t alloc_size = sizeof(struct aws_string) + len + 1;
  struct aws_string *str = bounded_malloc(alloc_size);

  if (str) {
    memhavoc(str, alloc_size); // only memhavoc if allocation succeeded
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

struct aws_string *ensure_string_is_allocated_nondet_length(void) {
  /* Considers any size up to the maximum possible size for the array [bytes] in
   * aws_string. However, for klee, we need to concretize symbolic size before allocation
   * set 256 as temporary solution
   */
  return ensure_string_is_allocated_bounded_length(KLEE_MAX_STRING_SIZE - 1 -
                                                   sizeof(struct aws_string));
}

// This takes in a ptr to an allocated piece of memory with the desired
// string len and initializes the string.
static void sea_init_str(char *str, size_t str_len) {
  str[str_len] = '\0';
  size_t max_string_len = sea_max_string_len();
  for (size_t j = 0; j < max_string_len; j++) {
    if (j < str_len) {
      assume(str[j] != '\0');
    }
  }
}

static const char *_ensure_c_str_is_nd_allocated(size_t max_size, size_t *len,
                                          bool safe) {
    size_t alloc_size;
    alloc_size = nd_size_t();
    // allocate size (0, max_size]
    assume(alloc_size > 0);
    assume(alloc_size <= max_size);

    char *str = NULL;
    if (safe) {
      str = bounded_malloc(alloc_size);
    }
    else {
      str = can_fail_malloc(alloc_size);
      if (!str) {
        return NULL;
      }
    }
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

static const char *
_ensure_c_str_is_nd_allocated_aligned(size_t max_size, size_t *len, bool safe) {
  size_t alloc_size;
  alloc_size = nd_size_t();
  // allocate no more than sea_max_string_len() + 1
  assume(alloc_size > 0);
  assume(alloc_size <= max_size);
  assume(max_size <= sea_max_string_len());

  // this allocation never fails
  char *str;
  str = sea_malloc_aligned_havoc(alloc_size);
  if (safe)
    assume(str);
  if (!str)
    return NULL;

  sea_init_str(str, alloc_size - 1);
  *len = alloc_size - 1;
  return str;
}

// This can return a NULL ptr. len will be zero in this case.
const char *ensure_c_str_is_nd_allocated(size_t max_size, size_t *len) {
  return _ensure_c_str_is_nd_allocated(max_size, len, false);
}

// This can return a NULL ptr. len will be zero in this case.
const char *ensure_c_str_is_nd_allocated_aligned(size_t max_size, size_t *len) {
  return _ensure_c_str_is_nd_allocated_aligned(max_size, len, false);
}

/** Allocate a randomly initialized string with a range of maximal length
 */
const char *ensure_c_str_is_nd_allocated_safe(size_t max_size, size_t *len) {
  return _ensure_c_str_is_nd_allocated(max_size, len, true);
}