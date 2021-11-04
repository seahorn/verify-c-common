#include <aws/common/math.h>
#include <aws/common/private/hash_table_impl.h>

#include <seahorn/seahorn.h>

#include <hash_table_helper.h>
#include <proof_allocators.h>
#include <utils.h>
#include <nondet.h>

uint64_t nd_hash_fn(const void *key) {
  (void) key;
  return nd_uint64_t();
}

bool nd_hash_equals_fn(const void *a, const void *b) {
  return nd_bool();
}

void hash_proof_destroy_noop(void *p) {}
void initialize_bounded_aws_hash_table(struct aws_hash_table *map,
                                       size_t max_table_entries) {
  size_t num_entries = nd_size_t();
  num_entries %= max_table_entries;
  size_t cur_num_entries = num_entries;
  // still aborts if overflow
  assume(aws_round_up_to_power_of_two(cur_num_entries, &num_entries) == AWS_OP_SUCCESS);

  size_t required_bytes;
  /* assume setting required_bytes is successful */
  assume(hash_table_state_required_bytes(num_entries, &required_bytes) ==
         AWS_OP_SUCCESS);
  struct hash_table_state *impl = bounded_malloc_havoc(required_bytes);
  impl->size = num_entries;
  impl->mask = num_entries - 1;
  impl->max_load_factor = 0.95;
  impl->alloc = sea_allocator();
  impl->hash_fn = &nd_hash_fn;
  impl->equals_fn = &nd_hash_equals_fn;
#ifdef EXPLICIT_HASH_INIT
  /** hash_table_state is implicitly initializaed by memhavoc() inside bounded_malloc_havoc() */
  impl->destroy_key_fn = &hash_proof_destroy_noop;
  impl->destroy_value_fn = &hash_proof_destroy_noop;
  impl->entry_count = nd_size_t();
  impl->max_load = nd_size_t();
#endif

  map->p_impl = impl;
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

bool hash_table_state_has_an_empty_slot(
    const struct hash_table_state *const state, size_t *const rval) {
  // assume(state->entry_count > 0);
  if (state->entry_count == 0) return false;
  for (size_t i = 0; i < state->size; i++) {
    const struct hash_table_entry *entry = &state->slots[i];
    if (entry->hash_code == 0) {
      return true;
    }
  }
  return false;
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

enum aws_hash_iter_status nd_hash_iter_status() {
    enum aws_hash_iter_status status = nd_int();
    // status >= AWS_HASH_ITER_STATUS_DONE && status <= AWS_HASH_ITER_STATUS_READY_FOR_USE
                  // assume(status >= AWS_HASH_ITER_STATUS_DONE &&
                  //        status <= AWS_HASH_ITER_STATUS_READY_FOR_USE);
    status %= AWS_HASH_ITER_STATUS_READY_FOR_USE;
    status = status < AWS_HASH_ITER_STATUS_DONE ? AWS_HASH_ITER_STATUS_DONE : status;
    return status;
}

void initialize_aws_hash_iter(struct aws_hash_iter *iter,
                              struct aws_hash_table *map) {
  iter->map = map;
  iter->element.key = nd_voidp();
  iter->element.value = nd_voidp();
  iter->slot = nd_size_t();
  iter->limit = nd_size_t();
  // 0 < iter->limit <= iter->map->p_impl->size
  iter->limit %= iter->map->p_impl->size;
  if (iter->limit == 0)
    iter->limit = iter->map->p_impl->size;
  // iter->slot < iter->limit
  iter->slot %= iter->limit;
  iter->status = nd_hash_iter_status();
  if (iter->status == AWS_HASH_ITER_STATUS_READY_FOR_USE) {
      // assume(map->p_impl->slots[iter->slot].hash_code > 0);
      uint64_t slot_code = map->p_impl->slots[iter->slot].hash_code;
      map->p_impl->slots[iter->slot].hash_code = slot_code == 0 ? 1 : slot_code;
  }
}

void mk_valid_aws_hash_iter(struct aws_hash_iter *iter,
                            struct aws_hash_table *map) {
  initialize_aws_hash_iter(iter, map);
  assume(aws_hash_iter_is_valid(iter));
}

void ensure_hash_table_has_valid_destroy_functions(struct aws_hash_table *map) {
  map->p_impl->destroy_key_fn = nd_bool() ? NULL : hash_proof_destroy_noop;
  map->p_impl->destroy_value_fn = nd_bool() ? NULL : hash_proof_destroy_noop;
}

bool uninterpreted_equals(const void *const a, const void *const b) {
  return nd_bool();
}

void uninterpreted_destroy_fn(void *key_or_val) { /** noop **/ }
