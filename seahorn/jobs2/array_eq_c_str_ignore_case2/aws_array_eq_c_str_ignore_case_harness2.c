/*
 * 
 */

#include <seahorn/seahorn.h>
#include <aws/common/byte_buf.h>
#include <proof_allocators.h>
#include <string_helper.h>
#include <nondet.h>
#include <utils.h>

int main() {
  /* assumptions */
  size_t array_len = nd_size_t();
  assume(array_len <= MAX_BUFFER_SIZE);
  void *array = can_fail_malloc(MAX_BUFFER_SIZE);
  size_t str_len = 0;
  const char *c_str =
      ensure_c_str_is_nd_allocated_safe(MAX_BUFFER_SIZE, &str_len);

  /* save current state of the parameters */
  struct store_byte_from_buffer old_byte_from_array;
  save_byte_from_array((uint8_t *)array, array_len, &old_byte_from_array);
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
