
#include <proof_allocators.h>
#include <klee_switch.h>
#include <nondet.h>

void *bounded_malloc(size_t size) {
  return size == 0 ? NULL : malloc(alloc_size(size));
}

void *can_fail_malloc(size_t size) { 
    return nd_bool() ? NULL : bounded_malloc(size); 
}

/**
 *
 */
static void *s_malloc_allocator(struct aws_allocator *allocator, size_t size) {
  (void)allocator;
  return bounded_malloc(size);
}

/**
 */
static void s_free_allocator(struct aws_allocator *allocator, void *ptr) {
  (void)allocator;
  free(ptr);
}

static struct aws_allocator s_allocator_klee_static = {
    .mem_acquire = s_malloc_allocator,
    .mem_release = s_free_allocator,
    .mem_realloc = NULL,
    .mem_calloc = NULL,
};

struct aws_allocator *sea_allocator() {
  return &s_allocator_klee_static;
}