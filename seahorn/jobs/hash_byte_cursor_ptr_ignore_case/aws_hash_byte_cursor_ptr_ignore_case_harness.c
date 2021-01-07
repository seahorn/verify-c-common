/**
 */

#include <aws/common/byte_buf.h>

#include <seahorn/seahorn.h>

#include <byte_buf_helper.h>
#include <config.h>

int main(void) {
  /* parameters */
  struct aws_byte_cursor cur;
  initialize_byte_cursor(&cur);

  /* assumptions */
  assume(aws_byte_cursor_is_bounded(&cur, MAX_BUFFER_SIZE));
  assume(aws_byte_cursor_is_valid(&cur));
  assume(AWS_MEM_IS_READABLE(cur.ptr, cur.len));

  /* operation under verification */
  aws_hash_byte_cursor_ptr_ignore_case(&cur);

  /* assertions */
  sassert(aws_byte_cursor_is_valid(&cur));
  return 0;
}
