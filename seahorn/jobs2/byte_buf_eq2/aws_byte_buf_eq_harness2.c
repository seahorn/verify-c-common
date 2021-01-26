/*
 *
 */

#include <aws/common/byte_buf.h>
#include <byte_buf_helper.h>
#include <seahorn/seahorn.h>
#include <utils.h>

int main() {
  /* parameters */
  struct aws_byte_buf lhs;
  initialize_byte_buf(&lhs);
  struct aws_byte_buf rhs;
  initialize_byte_buf(&rhs);

  /* assumptions */
  assume(aws_byte_buf_is_valid(&lhs));
  if (nd_bool()) {
    rhs = lhs;
  } else {
    assume(aws_byte_buf_is_valid(&rhs));
  }

  sea_tracking_on();

  /* operation under verification */
  if (aws_byte_buf_eq(&lhs, &rhs)) {
    sassert(lhs.len == rhs.len);
    if (lhs.len > 0) {
      assert_bytes_match(lhs.buffer, rhs.buffer, lhs.len);
    }
  }

  /* assertions */
  sassert(aws_byte_buf_is_valid(&lhs));
  sassert(aws_byte_buf_is_valid(&rhs));

  sassert(!sea_is_modified((char *)&lhs));
  sassert(!sea_is_modified((char *)lhs.buffer));

  sassert(!sea_is_modified((char *)&rhs));
  sassert(!sea_is_modified((char *)rhs.buffer));

  return 0;
}
