
#include <proof_allocators.h>
#include <klee_switch.h>
#include <nondet.h>

#ifdef __SYMBIOTIC__
extern void klee_make_symbolic(void *, size_t, const char *);
extern void *__VERIFIER_malloc0(size_t size);
void *symb_malloc(size_t sz) {
  void *mem = __VERIFIER_malloc0(sz);
  klee_make_symbolic(mem, sz, "malloc0");
  return mem;
}
#endif

// Note this behaviour deviates from SEAHORN since this can fail to allocate
// memory.
void *bounded_malloc_havoc(size_t size) {
  #ifdef __SYMBIOTIC__
    void* data = size == 0 ? NULL : symb_malloc(size);
  #else
    void* data = size == 0 ? NULL : malloc(alloc_size(size));
  #endif
  if (data) {
    memhavoc(data, size);
  }
  return data;
}

void *can_fail_malloc_havoc(size_t size) {
    return nd_bool() ? NULL : bounded_malloc_havoc(size);
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

static struct aws_allocator s_allocator_klee_static = {
    .mem_acquire = s_malloc_allocator,
    .mem_release = s_free_allocator,
    .mem_realloc = NULL,
    .mem_calloc = NULL,
};

struct aws_allocator *sea_allocator() {
  return &s_allocator_klee_static;
}