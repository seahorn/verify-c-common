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
  struct aws_hash_table map;
  initialize_bounded_aws_hash_table(&map, MAX_TABLE_SIZE);
  assume(aws_hash_table_is_valid(&map));

  struct aws_hash_iter iter;
  mk_valid_aws_hash_iter(&iter, &map);

  enum aws_hash_iter_status old_status = iter.status;
  struct store_byte_from_buffer old_byte;
  save_byte_from_hash_table(&map, &old_byte);

  aws_hash_iter_next(&iter);

  sassert(aws_hash_iter_is_valid(&iter));
  sassert(iter.status == AWS_HASH_ITER_STATUS_DONE ||
          iter.status == AWS_HASH_ITER_STATUS_READY_FOR_USE);
  sassert(IMPLIES(old_status == AWS_HASH_ITER_STATUS_DONE,
                  iter.status == AWS_HASH_ITER_STATUS_DONE));
  sassert(aws_hash_table_is_valid(&map));
  assert_hash_table_unchanged(&map, &old_byte);
}
