/*
 *
 */

#include <aws/common/string.h>
#include <byte_buf_helper.h>
#include <seahorn/seahorn.h>
#include <stddef.h>
#include <string_helper.h>
#include <utils.h>

int main(void) {
  struct aws_string *str =
      nd_bool() ? ensure_string_is_allocated_nondet_length() : NULL;
  aws_string_destroy(str);

  return 0;
}
