#include <aws/common/hash_table.h>
#include <aws/common/private/hash_table_impl.h>

#include <seahorn/seahorn.h>

#include <config.h>
#include <hash_table_helper.h>
#include <utils.h>

int main(void) {
  /* data structure */
  struct aws_hash_table map;
  initialize_bounded_aws_hash_table(&map, MAX_TABLE_SIZE);
  assume(aws_hash_table_is_valid(&map));

  /* element to be created */
  size_t empty_slot_idx;
  assume(aws_hash_table_has_an_empty_slot(&map, &empty_slot_idx));
  void *key = nd_voidp();
  struct aws_hash_element elm;
  struct aws_hash_element *p_elem = &elm;
  bool get_p_elem = nd_bool();
  bool track_was_created = nd_bool();
  int was_created; // for storing tracked result

  struct hash_table_state old_state = *map.p_impl;

  /* operation under verification*/
  int rval = aws_hash_table_create(&map, key, get_p_elem ? &p_elem : NULL,
                                   track_was_created ? &was_created : NULL);

  /* assertions */
  sassert(aws_hash_table_is_valid(&map));
  if (rval == AWS_OP_SUCCESS) {
    if (track_was_created) {
      sassert(map.p_impl->entry_count == old_state.entry_count + was_created);
    } else {
      sassert(map.p_impl->entry_count == old_state.entry_count ||
              map.p_impl->entry_count == old_state.entry_count + 1);
    }
#ifdef __SEA_UNINTERP_FN__
    if (get_p_elem) {
      sassert(uninterpreted_equals(p_elem->key, key));
    }
#endif
  } else {
    sassert(map.p_impl->entry_count == old_state.entry_count);
  }

  return 0;
}