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

  struct store_byte_from_buffer old_byte;
  save_byte_from_hash_table(&map, &old_byte);

  struct aws_hash_iter iter = aws_hash_iter_begin(&map);

  sassert(aws_hash_iter_is_valid(&iter));
  sassert(iter.status == AWS_HASH_ITER_STATUS_DONE ||
          iter.status == AWS_HASH_ITER_STATUS_READY_FOR_USE);
  if (map.p_impl->entry_count == 0) {
    /* quote header file comment:
    "...This function cannot fail, but if there are no elements in the table,
    the returned iterator will return true for aws_hash_iter_done(&iter)."
    */
    sassert(aws_hash_iter_done(&iter));
  }
  sassert(aws_hash_table_is_valid(&map));
  assert_hash_table_unchanged(&map, &old_byte);
  return 0;
}
