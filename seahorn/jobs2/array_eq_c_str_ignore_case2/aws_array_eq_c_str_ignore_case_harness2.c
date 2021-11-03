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
  void *array = can_fail_malloc_havoc(MAX_BUFFER_SIZE);
  size_t str_len = 0;
  const char *c_str =
      ensure_c_str_is_nd_allocated_safe(MAX_BUFFER_SIZE, &str_len);

 
  /* pre-conditions */
  assume(array || (array_len == 0));
  assume(c_str);

  /* save current state of the parameters */
  sea_tracking_on();

  /* operation under verification */
    if (aws_array_eq_c_str_ignore_case(array, array_len, c_str)) {
        sassert(array_len == str_len);
    }

    /* asserts both parameters remain unchanged */
    sassert(!sea_is_modified((char *)array));
    sassert(!sea_is_modified((char *)c_str));

    return 0;
}
