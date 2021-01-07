/**
 */

#include <stddef.h>

#include <aws/common/hash_table.h>
#include <aws/common/string.h>

#include <seahorn/seahorn.h>

#include <proof_allocators.h>
#include <string_helper.h>
#include <utils.h>
#include <config.h>

int main(void) {
  struct aws_string *str =
    ensure_string_is_allocated_bounded_length(MAX_STRING_LEN);

  assume(aws_string_is_valid(str));

  aws_hash_callback_string_destroy(str);
  return 0;
}
