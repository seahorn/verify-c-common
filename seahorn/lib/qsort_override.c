
#include <stdint.h>
#include <stdlib.h>
#include <seahorn/seahorn.h>
#include <nondet.h>

#define MEM_IS_ACESSABLE(base, len) (((len) == 0) || (base))

void qsort(void *base, size_t num, size_t size, int (*compare)(const void *, const void *)) {
    assume(MEM_IS_ACESSABLE(base, num * size));
    if (num == 0) return; // If the list is empty
    size_t index_a = nd_size_t();
    assume(index_a < num);
    size_t index_b = nd_size_t();
    assume(index_b < num);
    if (index_a == index_b) return;
    compare((uint8_t *)base + (size * index_a), (uint8_t *)base + (size * index_b));
}
