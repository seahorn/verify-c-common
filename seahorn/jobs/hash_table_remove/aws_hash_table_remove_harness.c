#include <aws/common/hash_table.h>
#include <aws/common/private/hash_table_impl.h>

#include <hash_table_helper.h>
#include <seahorn/seahorn.h>
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
  struct aws_hash_element p_elem;
  bool get_p_elem = nd_bool();
  bool track_was_present = nd_bool();
  int was_present;

  struct hash_table_state old_state = *map.p_impl;

  /* assume the preconditions */
  assume(aws_hash_table_is_valid(&map));
  assume(AWS_OBJECT_PTR_IS_WRITABLE(&p_elem));
  assume(AWS_OBJECT_PTR_IS_WRITABLE(&was_present));

  int rval = aws_hash_table_remove(&map, key, get_p_elem ? &p_elem : NULL,
                                   track_was_present ? &was_present : NULL);
  sassert(aws_hash_table_is_valid(&map));
  if (rval == AWS_OP_SUCCESS) {
    if (track_was_present) {
      sassert(map.p_impl->entry_count == old_state.entry_count - was_present);
    } else {
      sassert(map.p_impl->entry_count == old_state.entry_count ||
              map.p_impl->entry_count == old_state.entry_count - 1);
    }
#ifdef __SEA_UNINTERP_FN__
    if (get_p_elem && track_was_present && was_present == 1) {
      sassert(uninterpreted_equals(p_elem.key, key));
    }
#endif
  } else {
    sassert(map.p_impl->entry_count == old_state.entry_count);
  }
  return 0;
}