/*
 *
 */

#include <aws/common/math.h>
#include <nondet.h>
#include <proof_allocators.h>
#include <stdarg.h>
#include <stdlib.h>

#include <sea_mem_helper.h>
#include <seahorn/seahorn.h>

void *realloc(void *ptr, size_t new_size) {
  if (ptr) {
    free(ptr);
  }
  return malloc(new_size);
}

#ifdef __SEA_AWS_ALLOCATOR__
#ifdef __SEA_AWS_REAL_ALLOCATOR__
/**
 *
 */
static void *s_calloc_allocator(struct aws_allocator *allocator, size_t num,
                                size_t size) {
  (void)allocator;
  return bounded_calloc(num, size);
}

/**
 *
 */
static void *s_malloc_allocator(struct aws_allocator *allocator, size_t size) {
  (void)allocator;
  return bounded_malloc(size);
}

/**
 * Since we always allocate with "malloc()", just free with "free()"
 */
static void s_free_allocator(struct aws_allocator *allocator, void *ptr) {
  (void)allocator;
  free(ptr);
}

/**
 *
 */
static void *s_realloc_allocator(struct aws_allocator *allocator, void *ptr,
                                 size_t oldsize, size_t newsize) {
  (void)allocator;
  (void)oldsize;
  return realloc(ptr, newsize);
}

static struct aws_allocator s_allocator_static = {
    .mem_acquire = s_malloc_allocator,
    .mem_release = s_free_allocator,
    .mem_realloc = s_realloc_allocator,
    .mem_calloc = s_calloc_allocator,
};

struct aws_allocator *_allocator() {
  return &s_allocator_static;
}
#else
/** Globally allocated static allocator */
static struct aws_allocator s_allocator_static = {
    /* All fields are NULL because they will never be accessed */
    .mem_acquire = NULL,
    .mem_release = NULL,
    .mem_realloc = NULL,
    .mem_calloc = NULL,
};
struct aws_allocator *_allocator() {
  return &s_allocator_static;
}
#endif

#else

struct aws_allocator *nd_allocator = NULL;
struct aws_allocator *_allocator() {
  if (nd_allocator == NULL)
    nd_allocator = nd_voidp();
  return nd_allocator;
}

#endif

void *bounded_calloc(size_t num, size_t size) {
  size_t required_bytes;
  assume(aws_mul_size_checked(num, size, &required_bytes) == AWS_OP_SUCCESS);
  assume(required_bytes <= MEM_BLOCK);
  void *ptr = malloc(required_bytes);
  memset(ptr, 0, required_bytes);
  return ptr;
}

extern NONDET_FN_ATTR bool nd_malloc_fail(void);
void *can_fail_malloc(size_t size) {
  return nd_malloc_fail() ? NULL : bounded_malloc(size);
}

void *bounded_malloc(size_t size) {
  assume(size <= MEM_BLOCK);
  void *ptr = malloc(size);
  // nd-initialize the array since if caller
  // assumes immediately after calling bounded_malloc
  // it will be a read before write causing the
  // compiler to treat it as undef behaviour
  // thereby removing the read.
  memhavoc(ptr, size);
  return ptr;
}

/** Pure bounded memory allocation
 
 Does not fail. Does not initialize memory.
*/
void *bounded_malloc_pure(size_t size) {
  assume(size <= MEM_BLOCK);
  void *ptr = malloc(size);
  return ptr;
}

#ifdef __SEAHORN__
#include "aws_mem.c"
#endif
