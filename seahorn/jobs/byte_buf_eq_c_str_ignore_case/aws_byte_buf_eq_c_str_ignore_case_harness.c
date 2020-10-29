/*
 * 
 */

#include <seahorn/seahorn.h>
#include <aws/common/byte_buf.h>
#include <byte_buf_helper.h>
#include <utils.h>

int main() {
  /* parameters */
  struct aws_byte_buf buf;
  initialize_byte_buf(&buf);
  size_t str_len;
  const char *c_str =
      ensure_c_str_is_nd_allocated_safe(MAX_BUFFER_SIZE, &str_len);

  /* assumptions */
  assume(aws_byte_buf_is_valid(&buf));

  /* save current state of the parameters */
  struct aws_byte_buf old = buf;
  struct store_byte_from_buffer old_byte;
  save_byte_from_array(buf.buffer, buf.len, &old_byte);
  struct store_byte_from_buffer old_byte_from_str;
  save_byte_from_array((uint8_t *)c_str, str_len, &old_byte_from_str);

  /* operation under verification */
    if (aws_byte_buf_eq_c_str_ignore_case(&buf, c_str)) {
        sassert(buf.len == str_len);
    }

    /* asserts both parameters remain unchanged */
    sassert(aws_byte_buf_is_valid(&buf));
    assert_byte_buf_equivalence(&buf, &old, &old_byte);
    if (str_len > 0) {
        assert_byte_from_buffer_matches((uint8_t *)c_str, &old_byte_from_str);
    }

    return 0;
}
