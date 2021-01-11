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
  assume(map.p_impl->destroy_key_fn == hash_proof_destroy_noop ||
         map.p_impl->destroy_key_fn == NULL);
  assume(map.p_impl->destroy_value_fn == hash_proof_destroy_noop ||
         map.p_impl->destroy_value_fn == NULL);

  size_t empty_slot_idx;
  assume(aws_hash_table_has_an_empty_slot(&map, &empty_slot_idx));

  struct hash_table_state *state = map.p_impl;

  struct aws_hash_iter iter;
  mk_valid_aws_hash_iter(&iter, &map);
  assume(iter.status == AWS_HASH_ITER_STATUS_READY_FOR_USE);

  aws_hash_iter_delete(&iter, nd_bool());
  sassert(aws_hash_iter_is_valid(&iter));
  sassert(iter.status == AWS_HASH_ITER_STATUS_DELETE_CALLED);
  return 0;
}
