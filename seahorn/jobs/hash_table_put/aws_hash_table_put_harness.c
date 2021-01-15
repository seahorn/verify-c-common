#include <aws/common/hash_table.h>
#include <aws/common/private/hash_table_impl.h>

#include <seahorn/seahorn.h>

#include <config.h>
#include <hash_table_helper.h>
#include <utils.h>

int main(void) {
  struct aws_hash_table map;
  initialize_bounded_aws_hash_table(&map, MAX_TABLE_SIZE);
  assume(aws_hash_table_is_valid(&map));
  map.p_impl->destroy_key_fn = nd_bool() ? NULL : hash_proof_destroy_noop;
  map.p_impl->destroy_value_fn = nd_bool() ? NULL : hash_proof_destroy_noop;

  size_t empty_slot_idx;
  assume(aws_hash_table_has_an_empty_slot(&map, &empty_slot_idx));

  void *key = nd_voidp();
  void *value = nd_voidp();
  bool track_was_created = nd_bool();
  int was_created;
  struct hash_table_state old_state = *map.p_impl;

  int rval = aws_hash_table_put(&map, key, value,
                                track_was_created ? &was_created : NULL);
  if (rval == AWS_OP_SUCCESS) {
    if (track_was_created) {
      sassert(map.p_impl->entry_count == old_state.entry_count + was_created);
    } else {
      sassert(map.p_impl->entry_count == old_state.entry_count ||
              map.p_impl->entry_count == old_state.entry_count + 1);
    }
  } else {
    sassert(map.p_impl->entry_count == old_state.entry_count);
  }

  return 0;
}