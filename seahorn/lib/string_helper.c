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

// This takes in a ptr to an allocated piece of memory with the desired
// string len and initializes the string.
void sea_init_str(const char *str, size_t str_len) {
  assume(str[str_len] == '\0');
  // The following assumption cannot be expressed
  // assume(forall j :: j < i ==> str[j] != '\0');
  // therefore, we say the following:
  for (size_t j = 0; j < MAX_STRING_LEN; j++) {
    if (j < str_len) {
      assume(str[j] != '\0');
    }
  }
}

// This cannot return a NULL ptr.
// Returned len is always > 0
const char *ensure_c_str_is_nd_allocated_safe(size_t max_size, size_t *len) {
  size_t alloc_size;
  alloc_size = nd_size_t();
  // allocate no more than MAX_STRING_LEN + 1
  assume(alloc_size > 0 && alloc_size <= max_size &&
         max_size <= MAX_STRING_LEN);
  // bounded_malloc never fails
  const char *str = bounded_malloc(alloc_size);
  if (!str) {
    *len = 0;
    return str;
  }
  sea_init_str(str, alloc_size - 1);
  *len = alloc_size - 1;
  return str;
}

// This can return a NULL ptr. len will be zero in this case.
const char *ensure_c_str_is_nd_allocated(size_t max_size, size_t *len) {
  size_t alloc_size;
  alloc_size = nd_size_t();
  assume(alloc_size > 0 && alloc_size <= max_size &&
         max_size <= MAX_STRING_LEN);
  const char *str = can_fail_malloc(alloc_size);
  if (!str) {
    *len = 0;
    return str;
  }
  sea_init_str(str, alloc_size - 1);
  *len = alloc_size - 1;
  return str;
}

#include "sea_string.c"
