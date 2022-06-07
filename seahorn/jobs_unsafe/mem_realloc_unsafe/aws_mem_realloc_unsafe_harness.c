/*
 * 
 */

#include <seahorn/seahorn.h>
#include <aws/common/allocator.h>
#include "proof_allocators.h"
#include "nondet.h"

int main() {

    struct aws_allocator *allocator = nd_bool() ? sea_allocator() : sea_allocator_with_realloc();

    void *data = NULL;

    size_t old_size = nd_size_t();

    size_t new_size = nd_size_t();
    assume(old_size <= new_size);

    aws_mem_realloc(allocator, (void **)&data, old_size, new_size);

    return 0;
}
