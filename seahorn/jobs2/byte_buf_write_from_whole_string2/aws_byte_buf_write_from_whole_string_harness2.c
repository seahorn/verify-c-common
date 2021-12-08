/*
 * 
 */

#include <seahorn/seahorn.h>
#include <aws/common/string.h>
#include <aws/common/byte_buf.h>
#include <byte_buf_helper.h>
#include <string_helper.h>
#include <utils.h>
#include <stddef.h>

int main(void) {
  struct aws_string *str =
      nd_bool() ? ensure_string_is_allocated_bounded_length(MAX_STRING_LEN)
                : NULL;
  struct aws_byte_buf buf;
  initialize_byte_buf(&buf);

  assume(aws_byte_buf_is_valid(&buf));

  /* save current state of the data structure */
  size_t buf_old_len = buf.len;
  size_t buf_old_capacity = buf.capacity;
  sea_tracking_on();

  size_t available_cap = buf.capacity - buf.len;
  bool nondet_parameter = nd_bool();

  /* operation under verification */
  if (aws_byte_buf_write_from_whole_string(nondet_parameter ? &buf : NULL,
                                           str) &&
      str) {
    sassert(aws_string_is_valid(str));
    sassert(available_cap >= str->len);
    if (nondet_parameter) {
      sassert(buf.len == buf_old_len + str->len);
      sassert(buf.capacity == buf_old_capacity);
      if (str->len > 0 && buf.len > 0) {
        assert_bytes_match(buf.buffer + buf_old_len, str->bytes, str->len);
      }
    }
  } else {
    sassert(!sea_is_modified((char *)&buf));
    sassert(!sea_is_modified((char *)buf.buffer));
  }

  sassert(aws_byte_buf_is_valid(&buf));

  sassert(!sea_is_modified((char *)buf.allocator));

  return 0;
}
