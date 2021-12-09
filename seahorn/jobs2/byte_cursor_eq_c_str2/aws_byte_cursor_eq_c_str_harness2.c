/*
 *
 */

#include <seahorn/seahorn.h>
#include <aws/common/byte_buf.h>
#include <byte_buf_helper.h>
#include <string_helper.h>
#include <utils.h>

int main() {
  /* parameters */
  struct aws_byte_cursor cur;
  initialize_byte_cursor(&cur);
  size_t str_len;
  const char *c_str =
      ensure_c_str_is_nd_allocated_safe(MAX_BUFFER_SIZE, &str_len);

  /* assumptions */
  assume(aws_byte_cursor_is_valid(&cur));

  /* save current state of the parameters */
  struct aws_byte_cursor old = cur;
  sea_tracking_on();
  sea_reset_modified((char *)cur.ptr);
  sea_reset_modified((char *)c_str);

  /* operation under verification */
    if (aws_byte_cursor_eq_c_str(&cur, c_str)) {
        sassert(cur.len == str_len);
        if (cur.len > 0) {
            assert_bytes_match(cur.ptr, (uint8_t *)c_str, cur.len);
        }
    }

    /* asserts both parameters remain unchanged */
    sassert(aws_byte_cursor_is_valid(&cur));
    if (cur.len > 0) {
        sassert(!sea_is_modified((char *)cur.ptr));
    }
    if (str_len > 0) {
        sassert(!sea_is_modified((char *)c_str));
    }

    return 0;
}
