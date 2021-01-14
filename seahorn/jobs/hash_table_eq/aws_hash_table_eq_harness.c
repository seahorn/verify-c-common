#include <aws/common/hash_table.h>
#include <aws/common/private/hash_table_impl.h>
#include <config.h>
#include <hash_table_helper.h>
#include <seahorn/seahorn.h>
#include <utils.h>

int main(void) {
  struct aws_hash_table map_a;
  initialize_bounded_aws_hash_table(&map_a, MAX_TABLE_SIZE);
  map_a.p_impl->equals_fn = nondet_equals;
  assume(aws_hash_table_is_valid(&map_a));
  struct store_byte_from_buffer old_byte_a;
  save_byte_from_hash_table(&map_a, &old_byte_a);

  struct aws_hash_table map_b;
  initialize_bounded_aws_hash_table(&map_b, MAX_TABLE_SIZE);
  map_b.p_impl->equals_fn = nondet_equals;
  assume(aws_hash_table_is_valid(&map_b));
  struct store_byte_from_buffer old_byte_b;
  save_byte_from_hash_table(&map_b, &old_byte_b);

  bool rval = aws_hash_table_eq(&map_a, &map_b, nondet_equals);

  sassert(aws_hash_table_is_valid(&map_a));
  sassert(aws_hash_table_is_valid(&map_b));
  assert_hash_table_unchanged(&map_a, &old_byte_a);
  assert_hash_table_unchanged(&map_b, &old_byte_b);
  return 0;
}