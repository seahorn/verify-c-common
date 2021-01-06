#include <aws/common/hash_table.h>
#include <nondet.h>
#include <seahorn/seahorn.h>

int main(void) {
  /* hash value of ptr itself only, so deref should be illegal */
  void *ptr = nd_voidp();
  /* This function has no pre or post conditions */
  /* passively checks mem safety */
  uint64_t rval = aws_hash_ptr(ptr);
}