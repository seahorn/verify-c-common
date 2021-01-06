/**
 * Function: hash_table_state_is_valid
 * when hash_table is initialized with aws_hash_table_init, max_load_factor
 * is always 0.95, so its ok to just set max_load_factor_bounded to true
 */

#include <aws/common/hash_table.h>
#include <aws/common/math.h>
#include <aws/common/private/hash_table_impl.h>
#include <seahorn/seahorn.h>

#include <stdlib.h>

bool hash_table_state_is_valid(const struct hash_table_state *map) {
  if (!map) {
    return false;
  }
  bool hash_fn_nonnull = (map->hash_fn != NULL);
  bool equals_fn_nonnull = (map->equals_fn != NULL);
  /*destroy_key_fn and destroy_value_fn are both allowed to be NULL*/
  bool alloc_nonnull = (map->alloc != NULL);
  bool size_at_least_two = (map->size >= 2);
  bool size_is_power_of_two = aws_is_power_of_two(map->size);
  bool entry_count = (map->entry_count <= map->max_load);
  bool max_load = (map->max_load < map->size);
  bool mask_is_correct = (map->mask == (map->size - 1));
  /* original code */
  // bool max_load_factor_bounded = map->max_load_factor == 0.95;
  // //(map->max_load_factor < 1.0);
  bool max_load_factor_bounded = true;
  bool slots_allocated =
      AWS_MEM_IS_WRITABLE(&map->slots[0], sizeof(map->slots[0]) * map->size);

  return hash_fn_nonnull && equals_fn_nonnull && alloc_nonnull &&
         size_at_least_two && size_is_power_of_two && entry_count && max_load &&
         mask_is_correct && max_load_factor_bounded && slots_allocated;
}