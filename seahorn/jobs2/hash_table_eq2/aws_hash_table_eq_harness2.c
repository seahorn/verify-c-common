#include <aws/common/hash_table.h>
#include <aws/common/private/hash_table_impl.h>
#include <config.h> 
#include <hash_table_helper.h>
#include <seahorn/seahorn.h>
#include <utils.h> 
int main(void) {
  /* parameters */
  struct aws_hash_table map_a;
  initialize_bounded_aws_hash_table(&map_a, MAX_TABLE_SIZE);
  map_a.p_impl->equals_fn = nondet_equals;
  struct aws_hash_table map_b;
  initialize_bounded_aws_hash_table(&map_b, MAX_TABLE_SIZE);
  map_b.p_impl->equals_fn = nondet_equals;

  /* assumptions */
  assume(aws_hash_table_is_valid(&map_a));
  assume(aws_hash_table_is_valid(&map_b));

  /* save current state */
  sea_tracking_on();
  sea_reset_modified((char *)map_a.p_impl);
  sea_reset_modified((char *)map_b.p_impl);

  /* operation under verification */
  bool rval = aws_hash_table_eq(&map_a, &map_b, nondet_equals);

  /* assertions */
  sassert(aws_hash_table_is_valid(&map_a));
  sassert(aws_hash_table_is_valid(&map_b));

  sassert(!sea_is_modified((char *)map_a.p_impl));
  sassert(!sea_is_modified((char *)map_b.p_impl));

  return 0;
}
