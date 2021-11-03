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
  struct aws_byte_buf buf;
  initialize_byte_buf(&buf);
  size_t str_len;
  const char *c_str =
      ensure_c_str_is_nd_allocated_safe(MAX_BUFFER_SIZE, &str_len);

  /* assumptions */
  assume(aws_byte_buf_is_valid(&buf));

  /* save current state of the parameters */
  sea_tracking_on();


  /* operation under verification */
    if (aws_byte_buf_eq_c_str(&buf, c_str)) {
        sassert(buf.len == str_len);
        if (buf.len > 0) {
            assert_bytes_match(buf.buffer, (uint8_t *)c_str, buf.len);
        }
    }

    /* asserts both parameters remain unchanged */
    sassert(!sea_is_modified((char *)&buf));
    sassert(!sea_is_modified((char *)buf.buffer));
    sassert(!sea_is_modified((char *)c_str));

    return 0;
}
