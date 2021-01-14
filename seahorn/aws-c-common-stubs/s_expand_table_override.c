#include <aws/common/hash_table.h>
#include <aws/common/private/hash_table_impl.h>

#include <seahorn/seahorn.h>

#include <hash_table_helper.h>
#include <proof_allocators.h>
/**
 * Function s_expand_table
 * make non-det new_state with twice size and some empty slots
 */

int s_expand_table(struct aws_hash_table *map) {
  struct hash_table_state *old_state = map->p_impl;
  struct hash_table_state template = *old_state;

  size_t new_size;
  if (aws_mul_size_checked(template.size, 2, &new_size)) {
    return AWS_OP_ERR;
  }

  if (s_update_template_size(&template, new_size)) {
    return AWS_OP_ERR;
  }

#ifdef __SEAHORN__
  /* Don't use s_alloc_state because that will call calloc and we want non-det
   * values for the entries */
  size_t required_bytes = sizeof(struct hash_table_state) +
                          template.size * sizeof(struct hash_table_entry);
  struct hash_table_state *new_state = can_fail_malloc(required_bytes);
#else
  /* An empty slot has hashcode 0. So this marks all slots as empty */
  struct hash_table_state *new_state = s_alloc_state(&template);
#endif

  if (!new_state) {
    return AWS_OP_ERR;
  }

#ifdef __SEAHORN__
  *new_state = template;
  assume(aws_hash_table_is_valid(map));
  size_t empty_slot_idx;
  assume(aws_hash_table_has_an_empty_slot(map, &empty_slot_idx));
#else
  for (size_t i = 0; i < old_state->size; i++) {
    struct hash_table_entry entry = old_state->slots[i];
    if (entry.hash_code) {
      /* We can directly emplace since we know we won't put the same item twice
       */
      s_emplace_item(new_state, entry, 0);
    }
  }
#endif
  map->p_impl = new_state;
  aws_mem_release(new_state->alloc, old_state);

  return AWS_OP_SUCCESS;
}