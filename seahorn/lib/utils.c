/*
 * 
 */

#include <seahorn/seahorn.h>
#include <aws/common/private/hash_table_impl.h>
#include <proof_allocators.h>
#include <utils.h>

void assert_bytes_match(
    const uint8_t *const a, 
    const uint8_t *const b, 
    const size_t len) {
    sassert(!a == !b);
    if (len > 0 && a != NULL && b != NULL) {
        size_t i = nd_size_t();
        /* prevent spurious pointer overflows */
        assume(i < len && len < MAX_MALLOC); 
        sassert(a[i] == b[i]);
    }
}

void assert_all_bytes_are(
    const uint8_t *const a, 
    const uint8_t c, 
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
    const uint8_t *const buffer, 
    const struct store_byte_from_buffer *const b) {
    if (buffer && b) {
        sassert(*(buffer + b->index) == b->byte);
    }
}

void save_byte_from_array(
    const uint8_t *const array, 
    const size_t size, 
    struct store_byte_from_buffer *const storage) {
    storage->index = nd_size_t();
    if (size > 0 && array && storage) {
        assume(storage->index < size);
        storage->byte = array[storage->index];
    }
    else {
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
    const struct aws_byte_buf *const lhs,
    const struct aws_byte_buf *const rhs,
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

size_t sea_strlen(const char *str, size_t max) {
    size_t i;
    i = nd_size_t();
    assume(i < max && max <= MAX_BUFFER_SIZE);
    assume(str[i] == '\0');
    // The following assumption cannot be expressed
    // assume(forall j :: j < i ==> str[j] != '\0');
    // therefore, we say the following:
    size_t j = 0;
    for (j = 0; j < MAX_BUFFER_SIZE; j++) {
        if (j < i) { 
            assume(str[j] != '\0'); 
        }
    }
    return i;
}

const char *ensure_c_str_is_nd_allocated(size_t max_size, size_t *len) {
    // use bounded_nd_malloc to ensure that string is initialized
    const char *str = bounded_malloc(MAX_BUFFER_SIZE);
    *len = sea_strlen(str, max_size);
    return str;
}

const char *ensure_c_str_is_allocated(size_t max_size) {
    size_t cap = nd_size_t();
    assume(cap > 0 && cap <= max_size);
    assume (max_size <= MAX_BUFFER_SIZE);
    const char *str = bounded_malloc(MAX_BUFFER_SIZE);
    /* Ensure that its a valid c string. Since all bytes are nondeterminstic, 
     * the actual string length is 0..str_cap
     */
    assume(str[cap - 1] == 0);
    return str;
}
