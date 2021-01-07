/**
 */

#include <aws/common/hash_table.h>
#include <aws/common/private/hash_table_impl.h>
#include <aws/common/string.h>

#include <seahorn/seahorn.h>

#include <config.h>
#include <proof_allocators.h>
#include <string_helper.h>
#include <utils.h>

int main(void) {
  size_t len;
  const char *str = ensure_c_str_is_nd_allocated_aligned(MAX_STRING_LEN, &len);

  assume(aws_c_string_is_valid(str));

  uint64_t rval = aws_hash_c_string(str);
  (void)rval;
  return 0;
}
