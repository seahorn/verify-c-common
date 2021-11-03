/*
 * 
 */

#include "nondet.h"
#include <seahorn/seahorn.h>
#include <aws/common/byte_buf.h>
#include <proof_allocators.h>
#include <string_helper.h>
#include <utils.h>

int main() {
  /* assumptions */
  size_t array_len = nd_size_t();
  assume(array_len <= MAX_BUFFER_SIZE);
  uint8_t *array = bounded_malloc(array_len);

  size_t str_len = 0;
  const char *c_str =
      ensure_c_str_is_nd_allocated_safe(MAX_BUFFER_SIZE, &str_len);

  /* pre-conditions */
  assume(array || (array_len == 0));
  assume(c_str);

  /* save current state of the parameters */
  sea_tracking_on();

  /* operation under verification */
    if (aws_array_eq_c_str(array, array_len, c_str)) {
        /* asserts equivalence */
        sassert(array_len == str_len);
        if (array_len > 0) {
            assert_bytes_match(array, (uint8_t *)c_str, array_len);
        }
    }

    /* asserts both parameters remain unchanged */
    sassert(!sea_is_modified((char *)array));
    sassert(!sea_is_modified((char *)c_str));

    return 0;
}
