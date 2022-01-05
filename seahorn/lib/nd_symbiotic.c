#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


/**------------- Begin symbiotic nd definitions -------------------**/
// Note, all nondet calls are followed by non determined calls located at lib/verifier
extern int __VERIFIER_nondet_int(void);
extern int __VERIFIER_nondet_uint(void);
extern bool __VERIFIER_nondet_bool(void);
extern void __VERIFIER_assume(int expr);
extern void __VERIFIER_error() __attribute__ ((__noreturn__));
extern void __VERIFIER_assert(int expr);
extern int __VERIFIER_nondet_size_t(void);
extern unsigned short __VERIFIER_nondet_ushort(void);
extern unsigned char __VERIFIER_nondet_u8(void);
extern unsigned char __VERIFIER_nondet_uchar(void);
extern unsigned short __VERIFIER_nondet_u16(void);
extern unsigned int __VERIFIER_nondet_u32(void);
extern unsigned long __VERIFIER_nondet_ulong(void);
extern void *__VERIFIER_nondet_pointer(void);
extern void *__VERIFIER_malloc(size_t size);
extern void *__VERIFIER_malloc0(size_t size);
extern void klee_make_symbolic(void *addr, size_t nbytes, const char *name);
/**------------- End symbiotic nd definitions -------------------**/

size_t nd_size_t(void) {
  return __VERIFIER_nondet_ulong();
}

bool nd_bool(void) {
  return __VERIFIER_nondet_bool();
}

int nd_int(void) {
  return __VERIFIER_nondet_int();
}

uint8_t nd_uint8_t(void) {
  return (uint8_t)__VERIFIER_nondet_uchar();
}

uint16_t nd_uint16_t(void) {
  return __VERIFIER_nondet_ushort();
}

uint32_t nd_uint32_t(void) {
  return __VERIFIER_nondet_uint();
}

uint64_t nd_uint64_t(void) {
  return __VERIFIER_nondet_ulong();
}

void __SEA_assume(bool pre_cond) {
  __VERIFIER_assume(pre_cond);
}

void *nd_voidp(void) {
    return __VERIFIER_nondet_pointer();
}

bool nd_malloc_is_fail(void) { return nd_bool(); }

struct aws_linked_list_node *nd_linked_list_node(void) {
  return (struct aws_linked_list_node *)nd_voidp();
}

void *malloc(size_t sz) {
  return __VERIFIER_malloc0(sz);
}