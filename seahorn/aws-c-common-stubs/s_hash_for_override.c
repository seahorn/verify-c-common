#include <aws/common/private/hash_table_impl.h>
#include <nondet.h>

uint64_t s_hash_for(struct hash_table_state *state, const void *key) {
  AWS_PRECONDITION(hash_table_state_is_valid(state));

  if (key == NULL) {
    /* The best answer */
    return 42;
  }

#ifdef __SEAHORN__
  uint64_t hash_code = nd_uint64_t();
#else
  uint64_t hash_code = state->hash_fn(key);
#endif
  if (!hash_code) {
    hash_code = 1;
  }
  AWS_RETURN_WITH_POSTCONDITION(hash_code, hash_code != 0);
}