/*
 *
 */

#include <proof_allocators.h>

#include <stdarg.h>
#include <stdlib.h>

#include <nondet.h>
#include <sea_allocators.h>
#include <seahorn/seahorn.h>

void *realloc(void *ptr, size_t new_size) { return sea_realloc(ptr, new_size); }

void *bounded_malloc_havoc(size_t size) {
  return size == 0 ? NULL : sea_malloc_havoc_safe(size);
}

void *can_fail_malloc_havoc(size_t size) {
  return size == 0 ? NULL : sea_malloc_havoc(size);
}

/**
 *
 */
static void *s_malloc_allocator(struct aws_allocator *allocator, size_t size) {
  (void)allocator;
#ifdef SEA_ALLOCATOR_CAN_FAIL
  return can_fail_malloc_havoc(size);
#else
  return bounded_malloc_havoc(size);
#endif
}

/**
 */
static void s_free_allocator(struct aws_allocator *allocator, void *ptr) {
  (void)allocator;
  free(ptr);
}

static void *s_realloc_allocator(struct aws_allocator *allocator, void *ptr, size_t oldsize, size_t newsize) {
  (void)allocator;
  (void)oldsize;
  AWS_FATAL_PRECONDITION(newsize);

  if (newsize <= oldsize) {
    return ptr;
  }

  /* newsize is > oldsize, need more memory */
  void *new_mem = s_malloc_allocator(allocator, newsize);

  if (ptr) {
    memcpy(new_mem, ptr, oldsize);
    s_free_allocator(allocator, ptr);
  }

  return new_mem;
}

static struct aws_allocator s_allocator_static = {
    .mem_acquire = s_malloc_allocator,
    .mem_release = s_free_allocator,
    .mem_realloc = NULL,
    .mem_calloc = NULL,
};

static struct aws_allocator s_allocator_with_realloc_static = {
    .mem_acquire = s_malloc_allocator,
    .mem_release = s_free_allocator,
    .mem_realloc = s_realloc_allocator,
    .mem_calloc = NULL,
};

struct aws_allocator *sea_allocator() {
  return &s_allocator_static;
}

struct aws_allocator *sea_allocator_with_realloc() {
  return &s_allocator_with_realloc_static;
}

#if 0
#ifdef __SEAHORN__
#include "allocator_override.c"
#endif
#endif
