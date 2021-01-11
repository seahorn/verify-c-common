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

  size_t empty_slot_idx;
  assume(aws_hash_table_has_an_empty_slot(&map, &empty_slot_idx));
  aws_hash_table_clear(&map);
  sassert(aws_hash_table_is_valid(&map));
  sassert(map.p_impl->entry_count == 0);
  struct hash_table_state *impl = map.p_impl;
  // check that the bytes in slots were zeroed
  assert_all_zeroes((uint8_t *)&impl->slots[0],
                    impl->size * sizeof(impl->slots[0]));
  return 0;
}