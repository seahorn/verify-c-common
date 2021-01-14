/*
Function stubed: s_safe_eq_check
Indirect call toequals_fn is non-deterministic anyways so its fine to replace
it with nd boolean function
*/
#include <aws/common/hash_table.h>
#include <nondet.h>
bool s_safe_eq_check(aws_hash_callback_eq_fn *equals_fn, const void *a,
                     const void *b) {
  /* Short circuit if the pointers are the same */
  if (a == b) {
    return true;
  }
  /* If one but not both are null, the objects are not equal */
  if (a == NULL || b == NULL) {
    return false;
  }
  /* If both are non-null, call the underlying equals fn */
#ifdef __SEAHORN__
  return nd_bool();
#else
  return equals_fn(a, b);
#endif
}