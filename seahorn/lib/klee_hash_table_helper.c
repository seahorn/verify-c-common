#include <aws/common/math.h>
#include <aws/common/private/hash_table_impl.h>

#include <seahorn/seahorn.h>

#include <hash_table_helper.h>
#include <proof_allocators.h>

uint64_t nd_hash_fn(const void *key) {
    return nd_uint64_t();
}
bool nd_hash_equals_fn(const void *a, const void *b){
    return nd_bool();
}
void hash_proof_destroy_noop(void *p) {}
void initialize_bounded_aws_hash_table(struct aws_hash_table *map,
                                       size_t max_table_entries) {
  size_t num_entries = nd_size_t();
  assume(num_entries >= 2);
  assume(num_entries <= max_table_entries);
  assume(aws_is_power_of_two(num_entries));

  size_t required_bytes;
  /* assume setting required_bytes is successful */
  assume(hash_table_state_required_bytes(num_entries, &required_bytes) ==
         AWS_OP_SUCCESS);
  struct hash_table_state *impl = bounded_malloc(required_bytes);
  impl->size = num_entries;
  impl->mask = num_entries - 1;
  impl->max_load_factor = 0.95;
  impl->alloc = sea_allocator();
  impl->hash_fn = &nd_hash_fn;
  impl->equals_fn = &nd_hash_equals_fn;
  impl->destroy_key_fn = &hash_proof_destroy_noop;
  impl->destroy_value_fn = &hash_proof_destroy_noop;
  impl->entry_count = nd_size_t();
  impl->max_load = nd_size_t();
  for (int idx = 0; idx < impl->size; ++idx)
    impl->slots[idx].hash_code = nd_uint64_t();
  // Preconditions adapted
  assume(impl->entry_count <= impl->max_load);
  assume(impl->max_load < impl->size);

  map->p_impl = impl;
}

// klee requires function call with a concretize implementation
enum aws_hash_iter_status nd_hash_iter_status() {
    enum aws_hash_iter_status status = nd_int();
    assume(status >= AWS_HASH_ITER_STATUS_DONE && 
        status <= AWS_HASH_ITER_STATUS_READY_FOR_USE);
    return status;
}

void initialize_aws_hash_iter(struct aws_hash_iter *iter,
                              struct aws_hash_table *map) {
  iter->map = map;
  iter->element.key = nd_voidp();
  iter->element.value = nd_voidp();
  iter->slot = nd_size_t();
  iter->limit = nd_size_t();
  assume(iter->limit <= iter->map->p_impl->size);
  iter->status = nd_hash_iter_status();
  if (iter->status == AWS_HASH_ITER_STATUS_READY_FOR_USE) {
      assume(iter->slot < iter->limit);
      assume(map->p_impl->slots[iter->slot].hash_code > 0);
  }
}

bool aws_hash_iter_is_valid_copy(const struct aws_hash_iter *iter) {
    if (!iter) {
        return false;
    }
    if (!iter->map) {
        return false;
    }
    if (!aws_hash_table_is_valid(iter->map)) {
        return false;
    }
    if (iter->limit > iter->map->p_impl->size) {
        return false;
    }

    switch (iter->status) {
        case AWS_HASH_ITER_STATUS_DONE:
            /* Done iff slot == limit */
            return iter->slot == iter->limit;
        case AWS_HASH_ITER_STATUS_DELETE_CALLED:
            /* iter->slot can underflow to SIZE_MAX after a delete
             * see the comments for aws_hash_iter_delete() */
            return iter->slot <= iter->limit || iter->slot == SIZE_MAX;
        case AWS_HASH_ITER_STATUS_READY_FOR_USE:
            /* A slot must point to a valid location (i.e. hash_code != 0) */
            return iter->slot < iter->limit && iter->map->p_impl->slots[iter->slot].hash_code != 0;
    }
    /* Invalid status code */
    return false;
}

void mk_valid_aws_hash_iter(struct aws_hash_iter *iter,
                            struct aws_hash_table *map) {
  initialize_aws_hash_iter(iter, map);
  assume(aws_hash_iter_is_valid_copy(iter));
}
void save_byte_from_hash_table(const struct aws_hash_table *map,
                               struct store_byte_from_buffer *storage) {
  struct hash_table_state *state = map->p_impl;
  size_t size_in_bytes;
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

void ensure_hash_table_has_valid_destroy_functions(struct aws_hash_table *map) {
  map->p_impl->destroy_key_fn = nd_bool() ? NULL : hash_proof_destroy_noop;
  map->p_impl->destroy_value_fn = nd_bool() ? NULL : hash_proof_destroy_noop;
}

bool hash_table_state_has_an_empty_slot(
    const struct hash_table_state *const state, size_t *const rval) {
  assume(state->entry_count > 0);
  size_t empty_slot_idx = nd_size_t();
  assume(empty_slot_idx < state->size);
  *rval = empty_slot_idx;
  return state->slots[empty_slot_idx].hash_code == 0;
}

bool aws_hash_table_has_an_empty_slot(const struct aws_hash_table *const map,
                                      size_t *const rval) {
  return hash_table_state_has_an_empty_slot(map->p_impl, rval);
}

size_t aws_hash_table_deep_entry_count(const struct aws_hash_table *const map) {
  struct hash_table_state *state = map->p_impl;
  size_t rval = 0;
  for (size_t i = 0; i < state->size; i++) {
    struct hash_table_entry *entry = &state->slots[i];
    if (entry->hash_code){
      rval++;
    }
  }
  return rval;
}

bool aws_hash_table_entry_count_is_valid(const struct aws_hash_table *const map) {
  return map->p_impl->entry_count == aws_hash_table_deep_entry_count(map);
}

bool aws_hash_table_deep_is_empty(const struct aws_hash_table *const map) {
  struct hash_table_state *state = map->p_impl;
  bool rval = true;
  for (size_t i = 0; i < state->size; i++) {
    struct hash_table_entry *entry = &state->slots[i];
    rval = rval && (entry->hash_code == 0);
  }
  return rval;
}
