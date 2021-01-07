/**
 */

#include <stddef.h>

#include <aws/common/hash_table.h>
#include <aws/common/string.h>

#include <seahorn/seahorn.h>

#include <proof_allocators.h>
#include <string_helper.h>
#include <utils.h>

int main(void) {
  const struct aws_string *str1 =
      ensure_string_is_allocated_bounded_length(MAX_STRING_LEN);
  const struct aws_string *str2 =
      nd_bool() ? str1
                : ensure_string_is_allocated_bounded_length(MAX_STRING_LEN);

  assume(aws_string_is_valid(str1));
  assume(aws_string_is_valid(str2));

  bool rval = aws_hash_callback_string_eq(str1, str2);
  if (rval) {
    sassert(str1->len == str2->len);
    assert_bytes_match(str1->bytes, str2->bytes, str1->len);
  }
  return 0;
}
