#include <aws/common/hash_table.h>
#include <nondet.h>
#include <seahorn/seahorn.h>
#include <string_helper.h>

int main(void) {
  /* hash value of ptr itself only, so deref should be illegal */
  struct aws_string *str =
      ensure_string_is_allocated_bounded_length(MAX_BUFFER_SIZE);
  /* This function has no pre or post conditions */
  /* passively checks mem safety */
  uint64_t rval = aws_hash_string(str);
}