#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/**
 * Mark nondet functions as not accessing memory
 * Note: if the attribute is too agressive, the optimizer might remove
 *       calls to nondet functions, thus reducing the amount of non-determinism.
 * Note: using each nondet function only once grately simplifies debugging.
 */
#define NONDET_FN_ATTR __declspec(noalias)

/**
 * Non-determinstic functions 
 */
extern NONDET_FN_ATTR bool nd_bool(void);
extern NONDET_FN_ATTR int nd_int(void);
extern NONDET_FN_ATTR size_t nd_size_t(void); 
extern NONDET_FN_ATTR uint16_t nd_uint16_t(void);
extern NONDET_FN_ATTR uint32_t nd_uint32_t(void);
extern NONDET_FN_ATTR uint64_t nd_uint64_t(void);
extern NONDET_FN_ATTR uint8_t nd_uint8_t(void);
extern void *nd_voidp(void) __attribute__((malloc));

/* store allocated mem size */
extern NONDET_FN_ATTR int nd_store_mem_size(void);

/**
 * Non-deterministic initialization of a memory segment.
 * Only accesses memory pointed by the argument (plus source of nondet values)
 * Note: might have different attribute from other nd() functions because it
 * actually accesses memory passed through arguments
 */
#define NDMEM_FN_ATTR __declspec(noalias)
extern NDMEM_FN_ATTR void memhavoc(void *ptr, size_t size);
