/*
 *
 */

#include <stdlib.h> // for exit()

#include <aws/common/private/hash_table_impl.h>
#include <bounds.h>
#include <proof_allocators.h>
#include <seahorn/seahorn.h>
#include <utils.h>

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

bool uninterpreted_predicate_fn(uint8_t value);