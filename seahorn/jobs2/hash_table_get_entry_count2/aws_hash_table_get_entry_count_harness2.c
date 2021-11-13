#include <aws/common/hash_table.h>
#include <aws/common/math.h>
#include <aws/common/private/hash_table_impl.h>

#include <seahorn/seahorn.h>

#include <hash_table_helper.h>
#include <proof_allocators.h>
#include <utils.h>

int main(void) {
  /* parameters */
  struct aws_hash_table table;
  /* There are no loops in the code under test, so use the biggest possible
   * value */
  initialize_bounded_aws_hash_table(&table, SIZE_MAX);

  /* assumptions */
  assume(aws_hash_table_is_valid(&table));

  /* save the current state */
  struct hash_table_state *state = table.p_impl;
  size_t old_entry_count = state->entry_count;

  sea_tracking_on();
  sea_reset_modified((char *)&table);
  sea_reset_modified((char *)table.p_impl);

  /* operation under verification */
  size_t rval = aws_hash_table_get_entry_count(&table);

  /* assertions */
  sassert(rval == old_entry_count);
  /* Ensure that the table remains valid */
  sassert(aws_hash_table_is_valid(&table));

  /* Ensure that table is unchanged */
  sassert(!sea_is_modified((char *)&table));
  sassert(!sea_is_modified((char *)table.p_impl));
  return 0;
}
