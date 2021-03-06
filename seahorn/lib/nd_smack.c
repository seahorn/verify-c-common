#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "smack/smack.h"

size_t nd_size_t(void) {
  return __VERIFIER_nondet_unsigned_int();
}

bool nd_bool(void) {
  return __VERIFIER_nondet_bool();
}

int nd_int(void) {
  return __VERIFIER_nondet_int();
}

uint8_t nd_uint8_t(void) {
  // unsigned char 1 bytes = 8 bits
  return __VERIFIER_nondet_unsigned_char();
}

uint16_t nd_uint16_t(void) {
  // unsigned short int = 2 bytes = 16 bits
  return __VERIFIER_nondet_unsigned_short_int();
}

uint32_t nd_uint32_t(void) {
  //unsigned int = 4 bytes = 32 bits

  return __VERIFIER_nondet_unsigned_int();
}

uint64_t nd_uint64_t(void) {
  // unsigned long long = 8 bytes = 64 bits
  return __VERIFIER_nondet_unsigned_long_long_int();
}

void __SEA_assume(bool pre_cond) {
  __VERIFIER_assume(pre_cond);
}

void __VERIFIER_error(void) {
  __VERIFIER_assert(0);
}

void *nd_voidp(void) {
    return __VERIFIER_nondet_pointer();
}

bool nd_malloc_is_fail(void) { return nd_bool(); }

/* nd_linked_list_node - special function for returning a symbolic value of
 * the linked list node pointer.
*/
struct aws_linked_list_node *nd_linked_list_node(void) {
  return (struct aws_linked_list_node *)nd_voidp();
}

#define INLINE __attribute__((always_inline))

// wrapper memcpy for smack
INLINE void *memcpy(void *dst, const void *src, size_t len) {
  // smack treats invalid pointer dereference to call memcpy if size n is zero.
  if (len == 0)
    return dst;
  return __builtin_memcpy(dst, src, len);
}