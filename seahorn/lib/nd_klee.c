#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

void klee_make_symbolic(void *addr, size_t nbytes, const char *name);
int klee_range(int begin, int end, const char *name);
int klee_int(const char *name);
void klee_assume(uintptr_t condition);

void __assert_fail(const char*, const char*, unsigned, const char*);

# define klee_assert(expr)                                            \
  ((expr)                                                             \
   ? (void) (0)                                                       \
   : __assert_fail (#expr, __FILE__, __LINE__, __PRETTY_FUNCTION__))  \

size_t nd_size_t(void) {
  return klee_int("size_t");
}

bool nd_bool(void) {
  return klee_int("bool");
}

uint64_t nd_uint64_t() {
  return klee_int("uint64_t");
}

uint32_t nd_uint32_t() {
  return klee_int("uint32_t");
}

void __VERIFIER_assert(bool v) {
  klee_assert(v);
}

void __VERIFIER_assume(bool v) {
  klee_assume(v);
}

void __VERIFIER_error(void) {
  klee_assert(0);
}

