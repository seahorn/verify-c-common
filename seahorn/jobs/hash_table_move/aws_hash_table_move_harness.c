#include <aws/common/hash_table.h>
#include <hash_table_helper.h>
#include <seahorn/seahorn.h>
#include <utils.h>

int main(void) {
  struct aws_hash_table to;
  struct aws_hash_table from;

  // There are no loops in the code under test, so use the biggest possible
  // value
  initialize_bounded_aws_hash_table(&from, SIZE_MAX);
  assume(aws_hash_table_is_valid(&from));

  struct store_byte_from_buffer stored_byte;
  save_byte_from_hash_table(&from, &stored_byte);

  aws_hash_table_move(&to, &from);

  // Ensure that the destination table is valid.
  sassert(aws_hash_table_is_valid(&to));

  // Ensure that the two tables were byte for byte swapped
  assert_hash_table_unchanged(&to, &stored_byte);
  return 0;
}