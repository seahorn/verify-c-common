#include <bounds.h>
#include <proof_allocators.h>
#include <sea_allocators.h>
#include <seahorn/seahorn.h>
#include <string_helper.h>

static void sea_init_str(char *str, size_t str_len);

struct aws_string *ensure_string_is_allocated(size_t len) {
  struct aws_string *str =
      sea_malloc_havoc_safe(sizeof(struct aws_string) + len + 1);

  if (str) {
    /* Fields are declared const, so we need to copy them in like this */
    #ifdef __CRAB__
    *(struct aws_allocator **)(&str->allocator) = sea_allocator();
    #else
    *(struct aws_allocator **)(&str->allocator) =
        nd_bool() ? sea_allocator() : NULL;
    #endif
    *(size_t *)(&str->len) = len;
    *(uint8_t *)&str->bytes[len] = '\0';
  }
  return str;
}

struct aws_string *ensure_string_is_allocated_bounded_length(size_t max_size) {
  size_t len = nd_size_t();
  #ifdef __CRAB__
  assume(len > 1);
  #endif
  assume(len < max_size);
  return ensure_string_is_allocated(len);
}

struct aws_string *ensure_string_is_allocated_nondet_length(void) {
  /* Considers any size up to the maximum possible size for the array [bytes] in
   * aws_string */
  return ensure_string_is_allocated_bounded_length(SIZE_MAX - 1 -
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
  // allocate no more than sea_max_string_len() + 1
  assume(alloc_size > 0);
  assume(alloc_size <= max_size);
  assume(max_size <= sea_max_string_len());

  // this allocation never fails
  char *str;
  if (safe) {
    str = sea_malloc_havoc_safe(alloc_size);
  } else {
    str = sea_malloc_havoc(alloc_size);
    if (!str) {
      return NULL;
    }
  }

  sea_init_str(str, alloc_size - 1);
  *len = alloc_size - 1;
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

// This can return a NULL ptr. len will be zero in this case.
const char *ensure_c_str_is_nd_allocated_safe(size_t max_size, size_t *len) {
  return _ensure_c_str_is_nd_allocated(max_size, len, true);
}
