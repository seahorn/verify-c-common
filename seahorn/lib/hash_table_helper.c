#include <aws/common/math.h>
#include <hash_table_helper.h>
#include <proof_allocators.h>
#include <seahorn/seahorn.h>
#include <utils.h>

void ensure_allocated_hash_table(struct aws_hash_table *map,
                                 size_t max_table_entries) {
  size_t num_entries = nd_size_t();
  assume(num_entries <= max_table_entries);
  assume(aws_is_power_of_two(num_entries));

  size_t required_bytes = nd_size_t();
  assume(!hash_table_state_required_bytes(num_entries, &required_bytes));
  struct hash_table_state *impl = bounded_malloc(required_bytes);
  impl->size = num_entries;
  map->p_impl = impl;
}
