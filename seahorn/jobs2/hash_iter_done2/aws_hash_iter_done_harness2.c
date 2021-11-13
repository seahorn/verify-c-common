/**
 */

#include <aws/common/hash_table.h>
#include <aws/common/private/hash_table_impl.h>

#include <seahorn/seahorn.h>

#include <config.h>
#include <hash_table_helper.h>
#include <proof_allocators.h>
#include <utils.h>

int main(void) {
  /* parameters */
  struct aws_hash_table map;
  initialize_bounded_aws_hash_table(&map, MAX_TABLE_SIZE);
  struct aws_hash_iter iter;
  mk_valid_aws_hash_iter(&iter, &map);

  /* assumptions */
  assume(aws_hash_table_is_valid(&map));
  assume(iter.status == AWS_HASH_ITER_STATUS_DONE ||
         iter.status == AWS_HASH_ITER_STATUS_READY_FOR_USE);

  /* save current state */
  sea_tracking_on();
  enum aws_hash_iter_status old_status = iter.status;
  sea_reset_modified((char *)&map);
  sea_reset_modified((char *)map.p_impl);

  /* operation under verification */
  bool rval = aws_hash_iter_done(&iter);

  /* assertions */
  sassert(aws_hash_iter_is_valid(&iter));
  sassert(rval == (iter.status == AWS_HASH_ITER_STATUS_DONE));
  sassert(iter.status == old_status);
  sassert(aws_hash_table_is_valid(&map));
  sassert(!sea_is_modified((char *)&map));
  sassert(!sea_is_modified((char *)map.p_impl));
  return 0;
}
