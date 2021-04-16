#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "smack.h"

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

void __VERIFIER_error(void) {
  __VERIFIER_assert(0);
}

/* memhavoc - Special function for memory block initialization. 
  * initialize memory content as non-deterministic value.
*/
void memhavoc(void *ptr, size_t size) {
  // TODO: Finish implement this
  return;
}

void *nd_voidp(void) {
    return __VERIFIER_nondet_pointer();
}

bool nd_malloc_is_fail(void) { return nd_bool(); }