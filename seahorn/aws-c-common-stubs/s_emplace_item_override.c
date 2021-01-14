#include <aws/common/hash_table.h>
#include <aws/common/private/hash_table_impl.h>

#include <seahorn/seahorn.h>

#include <utils.h>

/**
 * Function: s_emplace_item
 * replace iterating for empty slot with non-deterministically
 * finding empty slot
 */

struct hash_table_entry *s_emplace_item(struct hash_table_state *state,
                                        struct hash_table_entry entry,
                                        size_t probe_idx) {
  AWS_PRECONDITION(hash_table_state_is_valid(state));

  if (entry.hash_code == 0) {
    AWS_RETURN_WITH_POSTCONDITION(NULL, hash_table_state_is_valid(state));
  }

#ifdef __SEAHORN__
  size_t index = nd_size_t();
  assume(index < state->size);
  assume(state->slots[index].hash_code == 0);
  state->slots[index] = entry;
  AWS_POSTCONDITION(hash_table_state_is_valid(state),
                    "Output hash_table_state [state] must be valid.");
  return &state->slots[index];
#else
  /* original code */
  struct hash_table_entry *rval = NULL;

  /* Since a valid hash_table has at least one empty element, this loop will
   * always terminate in at most linear time
   */
  while (entry.hash_code != 0) {
#ifdef CBMC
#pragma CPROVER check push
#pragma CPROVER check disable "unsigned-overflow"
#endif
    size_t index = (size_t)(entry.hash_code + probe_idx) & state->mask;
#ifdef CBMC
#pragma CPROVER check pop
#endif
    struct hash_table_entry *victim = &state->slots[index];

#ifdef CBMC
#pragma CPROVER check push
#pragma CPROVER check disable "unsigned-overflow"
#endif
    size_t victim_probe_idx = (size_t)(index - victim->hash_code) & state->mask;
#ifdef CBMC
#pragma CPROVER check pop
#endif

    if (!victim->hash_code || victim_probe_idx < probe_idx) {
      /* The first thing we emplace is the entry itself. A pointer to its
       * location becomes the rval */
      if (!rval) {
        rval = victim;
      }

      struct hash_table_entry tmp = *victim;
      *victim = entry;
      entry = tmp;

      probe_idx = victim_probe_idx + 1;
    } else {
      probe_idx++;
    }
  }

  AWS_RETURN_WITH_POSTCONDITION(rval,
                                hash_table_state_is_valid(state) &&
                                    rval >= &state->slots[0] &&
                                    rval < &state->slots[state->size],
                                "Output hash_table_entry pointer [rval] must "
                                "point in the slots of [state].");
#endif
}