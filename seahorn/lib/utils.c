/*
 *
 */

#include <aws/common/private/hash_table_impl.h>
#include <proof_allocators.h>
#include <seahorn/seahorn.h>
#include <utils.h>

#include <stdlib.h> // for exit()


void assert_bytes_match(const uint8_t *const a, const uint8_t *const b,
                        const size_t len) {
  sassert(len == 0 || !a == !b);
  if (len > 0 && a != NULL && b != NULL) {
    size_t i = nd_size_t();
    /* prevent spurious pointer overflows */
    assume(i < len && len < MAX_MALLOC);
    sassert(a[i] == b[i]);
  }
}

void assert_all_bytes_are(const uint8_t *const a, const uint8_t c,
                          const size_t len) {
  if (len > 0 && a != NULL) {
    size_t i = nd_size_t();
    assume(i < len);
    sassert(a[i] == c);
  }
}

void assert_all_zeroes(const uint8_t *const a, const size_t len) {
  assert_all_bytes_are(a, 0, len);
}

void assert_byte_from_buffer_matches(
    const uint8_t *const buffer, const struct store_byte_from_buffer *const b) {
  if (buffer && b) {
    sassert(*(buffer + b->index) == b->byte);
  }
}

void save_byte_from_array(const uint8_t *const array, const size_t size,
                          struct store_byte_from_buffer *const storage) {
  storage->index = nd_size_t();
  if (size > 0 && array && storage) {
    assume(storage->index < size);
    storage->byte = array[storage->index];
  } else {
    storage->byte = nd_uint8_t();
  }
}

void assert_array_list_equivalence(
    const struct aws_array_list *const lhs,
    const struct aws_array_list *const rhs,
    const struct store_byte_from_buffer *const rhs_byte) {
  /* In order to be equivalent, either both are NULL or both are non-NULL */
  if (lhs == rhs) {
    return;
  } else {
    sassert(lhs && rhs); /* if only one is null, they differ */
  }
  sassert(lhs->alloc == rhs->alloc);
  sassert(lhs->current_size == rhs->current_size);
  sassert(lhs->length == rhs->length);
  sassert(lhs->item_size == rhs->item_size);
  if (lhs->current_size > 0) {
    assert_byte_from_buffer_matches((uint8_t *)lhs->data, rhs_byte);
  }
}

void assert_byte_buf_equivalence(
    const struct aws_byte_buf *const lhs, const struct aws_byte_buf *const rhs,
    const struct store_byte_from_buffer *const rhs_byte) {
  /* In order to be equivalent, either both are NULL or both are non-NULL */
  if (lhs == rhs) {
    return;
  } else {
    sassert(lhs && rhs); /* if only one is null, they differ */
  }
  sassert(lhs->len == rhs->len);
  sassert(lhs->capacity == rhs->capacity);
  sassert(lhs->allocator == rhs->allocator);
  if (lhs->len > 0) {
    assert_byte_from_buffer_matches(lhs->buffer, rhs_byte);
  }
}

void assert_byte_cursor_equivalence(
    const struct aws_byte_cursor *const lhs,
    const struct aws_byte_cursor *const rhs,
    const struct store_byte_from_buffer *const rhs_byte) {
  sassert(!lhs == !rhs);
  if (lhs && rhs) {
    sassert(lhs->len == rhs->len);
    if (lhs->len > 0) {
      assert_byte_from_buffer_matches(lhs->ptr, rhs_byte);
    }
  }
}

/* At least MAX_BUFFER_SIZE must be always defined */
#ifndef MAX_STRING_LEN
#define MAX_STRING_LEN MAX_BUFFER_SIZE
#endif

// This function is here for posterity only.
// Similar to `sea_strlen` it returns the length of a string
// but most importantly it creates a valid string of that length
// pointed to by `str`.
// OTOH `sea_strlen` is close to a conventional `strlen` and does not write to
// the string.
size_t sea_strlen_unused(const char *str, size_t max) {
  size_t i;
  i = nd_size_t();
  assume(i < max && max <= MAX_STRING_LEN);
  assume(str[i] == '\0');
  // The following assumption cannot be expressed
  // assume(forall j :: j < i ==> str[j] != '\0');
  // therefore, we say the following:
  size_t j = 0;
  for (j = 0; j < MAX_STRING_LEN; j++) {
    if (j < i) {
      assume(str[j] != '\0');
    }
  }
  return i;
}

// A strlen implementation.
// If the end-delimiter is not in offset <= max_size from start then
// 0 is returned.
size_t sea_strlen(const char *str, size_t max_size) {
  size_t len = 0;
  for (size_t i = 0; i < MAX_STRING_LEN; i++) {
    if (i <= max_size) {
      if (str[i] == '\0') {
        return len;
      }
      len++;
    }
  }
  return 0;
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

#ifdef __SEAHORN__
size_t strlen(const char *str) { return sea_strlen(str, MAX_STRING_LEN); }
#endif

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

#ifdef __SEAHORN__
#include "error.c"
#endif
