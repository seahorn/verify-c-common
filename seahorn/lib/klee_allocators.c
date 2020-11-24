
#include <proof_allocators.h>
#include <nondet.h>
size_t alloc_size(size_t sz) {
  switch(sz) {
    case 1: return 1;
    case 2: return 2;
    case 3: return 3;
    case 4: return 4;
    case 5: return 5;
    case 6: return 6;
    case 7: return 7;
    case 8: return 8;
    case 9: return 9;
    case 10: return 10;
    default: return sz <= 4096 ? 4096 : sz;
  }
}

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