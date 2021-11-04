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
  ensure_hash_table_has_valid_destroy_functions(&map);
  map.p_impl->alloc = sea_allocator();

  struct hash_table_state *state = map.p_impl;
  size_t empty_slot_idx;
  size_t size_in_bytes = sizeof(struct hash_table_state) +
                         sizeof(struct hash_table_entry) * state->size;

  // aws_hash_table_has_an_empty_slot
  assume(aws_hash_table_has_an_empty_slot(&map, &empty_slot_idx));
  aws_hash_table_clean_up(&map);
  sassert(map.p_impl == NULL);

  // this reads memory that has been freed, but we are not currently modelling
  // freeing memory
  #if defined(__KLEE__) || defined(__FUZZ__)
    // klee does not allow to access memory after free.
    // run-time UAF will be detected as by Address Sanitizer used by libFuzzer
  #else
  size_t i = nd_size_t();
  size_t len = state->size * sizeof(state->slots[0]);
  assume(i < len);
  uint8_t *bytes = (uint8_t *)&state->slots[0];
  sassert(bytes[i] == 0);
  #endif
  return 0;
}
