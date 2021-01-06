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

void *bounded_malloc(size_t size) {
  return size == 0 ? NULL : sea_malloc_havoc_safe(size);
}

void *can_fail_malloc(size_t size) {
  return size == 0 ? NULL : sea_malloc_havoc(size);
}

void *can_fail_calloc(size_t num, size_t size) {
  return size == 0 ? NULL : sea_calloc(num, size);
}

/**
 *
 */
static void *s_malloc_allocator(struct aws_allocator *allocator, size_t size) {
  (void)allocator;
  return bounded_malloc(size);
}

static void *s_can_fail_malloc_allocator(struct aws_allocator *allocator,
                                         size_t size) {
  (void)allocator;
  return can_fail_malloc(size);
}

static void *s_can_fail_calloc_allocator(struct aws_allocator *allocator,
                                         size_t num, size_t size) {
  (void)allocator;
  return can_fail_calloc(num, size);
}

/**
 */
static void s_free_allocator(struct aws_allocator *allocator, void *ptr) {
  (void)allocator;
  free(ptr);
}

static struct aws_allocator s_allocator_static = {
    .mem_acquire = s_malloc_allocator,
    .mem_release = s_free_allocator,
    .mem_realloc = NULL,
    .mem_calloc = NULL,
};

static struct aws_allocator s_can_fail_allocator = {
    .mem_acquire = s_can_fail_malloc_allocator,
    .mem_release = s_free_allocator,
    .mem_realloc = NULL,
    .mem_calloc = s_can_fail_calloc_allocator};

struct aws_allocator *sea_allocator() {
  return &s_allocator_static;
}

struct aws_allocator *sea_can_fail_allocator() {
  return &s_can_fail_allocator;
}

#if 0
#ifdef __SEAHORN__
#include "allocator_override.c"
#endif
#endif
