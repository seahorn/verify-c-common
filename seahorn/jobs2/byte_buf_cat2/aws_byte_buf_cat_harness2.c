/*
 *
 */

#include <aws/common/byte_buf.h>
#include <byte_buf_helper.h>
#include <seahorn/seahorn.h>
#include <utils.h>

/**
   SeaHorn does not support inlining of variable number of arguments functions.
   This is a specialization of aws_byte_buf_cat for 3 arguments.
 */
// -- specialize to 3 buffers
int aws_byte_buf_cat3(struct aws_byte_buf *dest, size_t number_of_args,
                      struct aws_byte_buf *buf1, struct aws_byte_buf *buf2,
                      struct aws_byte_buf *buf3) {
  AWS_PRECONDITION(aws_byte_buf_is_valid(dest));

  sassert(number_of_args == 3);
  struct aws_byte_cursor cursor = aws_byte_cursor_from_buf(buf1);
  if (aws_byte_buf_append(dest, &cursor)) {
    AWS_POSTCONDITION(aws_byte_buf_is_valid(dest));
    return AWS_OP_ERR;
  }

  cursor = aws_byte_cursor_from_buf(buf2);
  if (aws_byte_buf_append(dest, &cursor)) {
    AWS_POSTCONDITION(aws_byte_buf_is_valid(dest));
    return AWS_OP_ERR;
  }

  cursor = aws_byte_cursor_from_buf(buf3);
  if (aws_byte_buf_append(dest, &cursor)) {
    AWS_POSTCONDITION(aws_byte_buf_is_valid(dest));
    return AWS_OP_ERR;
  }

  AWS_POSTCONDITION(aws_byte_buf_is_valid(dest));
  return AWS_OP_SUCCESS;
}

int main() {
  /* parameters */
  struct aws_byte_buf buffer1;
  initialize_byte_buf(&buffer1);
  struct aws_byte_buf buffer2;
  initialize_byte_buf(&buffer2);
  struct aws_byte_buf buffer3;
  initialize_byte_buf(&buffer3);
  struct aws_byte_buf dest;
  initialize_byte_buf(&dest);
  size_t number_of_args = 3;

  /* assumptions */
  assume(aws_byte_buf_is_valid(&buffer1));
  assume(aws_byte_buf_is_valid(&buffer2));
  assume(aws_byte_buf_is_valid(&buffer3));
  assume(aws_byte_buf_is_valid(&dest));

  /* save current state of the data structure */
  struct aws_byte_buf old_buffer1 = buffer1;
  struct store_byte_from_buffer old_byte_from_buffer1;
  save_byte_from_array(buffer1.buffer, buffer1.len, &old_byte_from_buffer1);
  struct aws_byte_buf old_buffer2 = buffer2;
  struct store_byte_from_buffer old_byte_from_buffer2;
  save_byte_from_array(buffer2.buffer, buffer2.len, &old_byte_from_buffer2);
  struct aws_byte_buf old_buffer3 = buffer3;
  struct store_byte_from_buffer old_byte_from_buffer3;
  save_byte_from_array(buffer3.buffer, buffer3.len, &old_byte_from_buffer3);
  struct aws_byte_buf old_dest = dest;
  struct store_byte_from_buffer old_byte_from_dest;
  save_byte_from_array(dest.buffer, dest.len, &old_byte_from_dest);

  /* operation under verification */
  if (aws_byte_buf_cat3(&dest, number_of_args, &buffer1, &buffer2, &buffer3) ==
      AWS_OP_SUCCESS) {
    sassert((old_dest.capacity - old_dest.len) >=
            (buffer1.len + buffer2.len + buffer3.len));
  } else {
    sassert((old_dest.capacity - old_dest.len) <
            (buffer1.len + buffer2.len + buffer3.len));
  }

  /* assertions */
  sassert(aws_byte_buf_is_valid(&buffer1));
  sassert(aws_byte_buf_is_valid(&buffer2));
  sassert(aws_byte_buf_is_valid(&buffer3));
  sassert(aws_byte_buf_is_valid(&dest));
  assert_byte_buf_equivalence(&buffer1, &old_buffer1, &old_byte_from_buffer1);
  assert_byte_buf_equivalence(&buffer2, &old_buffer2, &old_byte_from_buffer2);
  assert_byte_buf_equivalence(&buffer3, &old_buffer3, &old_byte_from_buffer3);

  return 0;
}
