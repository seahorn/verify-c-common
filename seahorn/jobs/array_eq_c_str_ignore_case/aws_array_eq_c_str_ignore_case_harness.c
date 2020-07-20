/*
 * 
 */

#include <seahorn/seahorn.h>
#include <aws/common/byte_buf.h>
#include <proof_allocators.h>
#include <nondet.h>
#include <utils.h>

int main() {
    /* assumptions */
    size_t array_len = nd_size_t();
    assume(array_len <= MAX_BUFFER_SIZE);
    void *array = bounded_malloc(MAX_BUFFER_SIZE);
    const char *c_str = nd_bool() ? NULL : ensure_c_str_is_allocated(MAX_BUFFER_SIZE);

    /* save current state of the parameters */
    struct store_byte_from_buffer old_byte_from_array;
    save_byte_from_array((uint8_t *)array, array_len, &old_byte_from_array);
    size_t str_len = (c_str) ? sea_strlen(c_str) : 0;
    struct store_byte_from_buffer old_byte_from_str;
    save_byte_from_array((uint8_t *)c_str, str_len, &old_byte_from_str);

    /* pre-conditions */
    assume(array || (array_len == 0));
    assume(c_str);

    /* operation under verification */
    if (aws_array_eq_c_str_ignore_case(array, array_len, c_str)) {
        sassert(array_len == str_len);
    }

    /* asserts both parameters remain unchanged */
    if (array_len > 0) {
        assert_byte_from_buffer_matches((uint8_t *)array, &old_byte_from_array);
    }
    if (str_len > 0) {
        assert_byte_from_buffer_matches((uint8_t *)c_str, &old_byte_from_str);
    }

    return 0;
}
