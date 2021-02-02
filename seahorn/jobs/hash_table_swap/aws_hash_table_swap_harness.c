#include <aws/common/hash_table.h>
#include <hash_table_helper.h>
#include <seahorn/seahorn.h>
#include <utils.h>

int main(void) {
  struct aws_hash_table a;
  struct aws_hash_table b;
  struct store_byte_from_buffer stored_byte_a;
  struct store_byte_from_buffer stored_byte_b;

  /* There are no loops in the code under test, so use the biggest possible
   * value */
  /* Seahorn: initializing both lhs and rhs since init is non det anyways */
  #ifdef __KLEE__
  initialize_bounded_aws_hash_table(&a, MAX_TABLE_SIZE);
  #else
  // There are no loops in the code under test, so use the biggest possible
  // value
  initialize_bounded_aws_hash_table(&a, SIZE_MAX);
  #endif
  assume(aws_hash_table_is_valid(&a));
  save_byte_from_hash_table(&a, &stored_byte_a);

  #ifdef __KLEE__
  initialize_bounded_aws_hash_table(&b, MAX_TABLE_SIZE);
  #else
  // There are no loops in the code under test, so use the biggest possible
  // value
  initialize_bounded_aws_hash_table(&b, SIZE_MAX);
  #endif
  assume(aws_hash_table_is_valid(&b));
  save_byte_from_hash_table(&b, &stored_byte_b);

  aws_hash_table_swap(&a, &b);

  sassert(aws_hash_table_is_valid(&b));
  assert_hash_table_unchanged(&b, &stored_byte_a);
  sassert(aws_hash_table_is_valid(&a));
  assert_hash_table_unchanged(&a, &stored_byte_b);
  return 0;
}