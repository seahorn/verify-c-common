/** Memory allocating functions */
#include "sea_allocators.h"

#include "nondet.h"
#include <seahorn/seahorn.h>

extern void memhavoc(void *, size_t);

extern NONDET_FN_ATTR bool nd_malloc_is_fail(void);
INLINE void *sea_malloc(size_t sz) {
  #ifdef __CRAB__
  assume(sz > 0);
  return malloc(sz);
  #endif
  return nd_malloc_is_fail() ? NULL : malloc(sz);
}

// from: aws-c-common/source/allocator.c
#define AWS_ALIGN_ROUND_UP(value, alignment)                                   \
  (((value) + ((alignment)-1)) & ~((alignment)-1))
#ifdef __KLEE__
INLINE void *klee_malloc_aligned(size_t *sz) {
  enum { S_ALIGNMENT = sizeof(intmax_t) };
  *sz = AWS_ALIGN_ROUND_UP(*sz, S_ALIGNMENT);
  return sea_malloc(*sz);
}
#endif
INLINE void *sea_malloc_aligned(size_t sz) {
  enum { S_ALIGNMENT = sizeof(intmax_t) };
  size_t alloc_sz = AWS_ALIGN_ROUND_UP(sz, S_ALIGNMENT);
  return sea_malloc(alloc_sz);
}
#undef AWS_ALIGN_ROUND_UP

INLINE void *sea_malloc_havoc(size_t sz) {
  void *data = sea_malloc(sz);
  memhavoc(data, sz);
  return data;
}

INLINE void *sea_malloc_safe(size_t sz) {
  void *data = malloc(sz);
  assume(data);
  return data;
}

INLINE void *sea_malloc_havoc_safe(size_t sz) {
  void *data = sea_malloc_havoc(sz);
  assume(data);
  return data;
}

INLINE void *sea_malloc_aligned_safe(size_t sz) {
  void *data = sea_malloc_aligned(sz);
  assume(data);
  return data;
}

#ifdef __KLEE__
INLINE void *sea_malloc_aligned_havoc(size_t sz) {
  void *data = klee_malloc_aligned(&sz);
  if (data)
    memhavoc(data, sz);
  return data;
}
#else
INLINE void *sea_malloc_aligned_havoc(size_t sz) {
  void *data = sea_malloc_aligned(sz);
  memhavoc(data, sz);
  return data;
}
#endif

INLINE void sea_free(void *ptr) { free(ptr); }

INLINE void *sea_realloc(void *ptr, size_t sz) {
  if (ptr) sea_free(ptr);
  return sea_malloc(sz);
}
