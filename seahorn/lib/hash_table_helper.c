#include <aws/common/math.h>
#include <aws/common/private/hash_table_impl.h>

#include <seahorn/seahorn.h>

#include <hash_table_helper.h>
#include <proof_allocators.h>

void initialize_bounded_aws_hash_table(struct aws_hash_table *map,
                                       size_t max_table_entries) {
  size_t num_entries = nd_size_t();
  assume(num_entries <= max_table_entries);
  assume(aws_is_power_of_two(num_entries));

  size_t required_bytes = nd_size_t();
  /* assume setting required_bytes is successful */
  assume(hash_table_state_required_bytes(num_entries, &required_bytes) ==
         AWS_OP_SUCCESS);
  struct hash_table_state *impl = bounded_malloc(required_bytes);
  impl->size = num_entries;
  map->p_impl = impl;
}

extern NONDET_FN_ATTR enum aws_hash_iter_status nd_hash_iter_status(void);
void initialize_aws_hash_iter(struct aws_hash_iter *iter,
                              struct aws_hash_table *map) {
  iter->map = map;
  iter->element.key = nd_voidp();
  iter->element.value = nd_voidp();
  iter->slot = nd_size_t();
  iter->limit = nd_size_t();
  iter->status = nd_hash_iter_status();
}

void mk_valid_aws_hash_iter(struct aws_hash_iter *iter,
                            struct aws_hash_table *map) {
  initialize_aws_hash_iter(iter, map);
  assume(aws_hash_iter_is_valid(iter));
}
void save_byte_from_hash_table(const struct aws_hash_table *map,
                               struct store_byte_from_buffer *storage) {
  struct hash_table_state *state = map->p_impl;
  size_t size_in_bytes = nd_size_t();
  assume(hash_table_state_required_bytes(state->size, &size_in_bytes) ==
         AWS_OP_SUCCESS);
  save_byte_from_array((uint8_t *)state, size_in_bytes, storage);
}

void assert_hash_table_unchanged(const struct aws_hash_table *map,
                                 const struct store_byte_from_buffer *storage) {
  struct hash_table_state *state = map->p_impl;
  uint8_t *byte_array = (uint8_t *)state;
  assert_byte_from_buffer_matches((uint8_t *)state, storage);
}

void uninterpreted_destroy_fn(void *key_or_val);