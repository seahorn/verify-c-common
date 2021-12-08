/*
 *
 */

#include <proof_allocators.h>
#include "sea_allocators.h"
#include <stdarg.h>
#include <stdlib.h>

// for assume()
#include <seahorn/seahorn.h> 

// Note that for SEAHORN this function will always succeed in reserving memory
// For fuzzing, this may fail.
void *bounded_malloc_havoc(size_t size) {
  void* data = malloc(size);
  if (data) {
    memhavoc(data, size);
  }
  return data;
}

void *can_fail_malloc_havoc(size_t size) {
  void* data = malloc(size);
  if (data) {
    memhavoc(data, size);
  }
  return data;
}

void *sea_malloc_safe(size_t sz) {
  void *p = malloc(sz);
  assume(p);
  return p;
}

#define AWS_ALIGN_ROUND_UP(value, alignment) \
  (((value) + ((alignment)-1)) & ~((alignment)-1))

INLINE void *sea_malloc_aligned(size_t sz) {
  enum { S_ALIGNMENT = sizeof(intmax_t) };
  size_t alloc_sz = AWS_ALIGN_ROUND_UP(sz, S_ALIGNMENT);
  return malloc(alloc_sz);
}
#undef AWS_ALIGN_ROUND_UP

void *sea_malloc_aligned_havoc(size_t sz) {
  void *data = sea_malloc_aligned(sz);
  if (data)
    memhavoc(data, sz);
  return data;
}

/**
 *
 */
static void *s_malloc_allocator(struct aws_allocator *allocator, size_t size) {
  (void)allocator;
  return bounded_malloc_havoc(size);
}

/**
 */
static void s_free_allocator(struct aws_allocator *allocator, void *ptr) {
  (void)allocator;
  free(ptr);
}

static struct aws_allocator s_allocator_fuzz_static = {
    .mem_acquire = s_malloc_allocator,
    .mem_release = s_free_allocator,
    .mem_realloc = NULL,
    .mem_calloc = NULL,
};

struct aws_allocator *sea_allocator() {
  return &s_allocator_fuzz_static;
}
