#include <aws/common/hash_table.h>
#include <aws/common/math.h>
#include <aws/common/private/hash_table_impl.h>
#include <proof_allocators.h>
#include <seahorn/seahorn.h>
#include <utils.h>

int main(void) {
  struct aws_hash_table table;
  /* There are no loops in the code under test, so use the biggest possible
   * value */
  ensure_allocated_hash_table(&table, SIZE_MAX);
  assume(aws_hash_table_is_valid(&table));
  struct hash_table_state *state = table.p_impl;

  struct store_byte_from_buffer stored_byte;
  save_byte_from_hash_table(&table, &stored_byte);
  size_t old_entry_count = state->entry_count;
  // size_t rval = aws_hash_table_get_entry_count(&table);
  size_t rval = nd_size_t();
  sassert(rval == old_entry_count);
  /* Ensure that the table remains valid */
  sassert(aws_hash_table_is_valid(&table));

  /* Ensure that table is unchanged */
  check_hash_table_unchanged(&table, &stored_byte);
}