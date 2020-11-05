/** Custom version of aws_mem_XXX functions that directly call our custom
 * allocator */

#include <proof_allocators.h>

#include <stdarg.h>
#include <stdlib.h>

#include <aws/common/math.h>

/************************************************************************************/

void *aws_mem_acquire(struct aws_allocator *allocator, size_t size) {
  (void)allocator;
  void *mem = can_fail_malloc(size);
  if (!mem) {
    aws_raise_error(AWS_ERROR_OOM);
  }
  return mem;
}

void *aws_mem_calloc(struct aws_allocator *allocator, size_t num, size_t size) {
  (void)allocator;
  size_t required_bytes;
  if (aws_mul_size_checked(num, size, &required_bytes)) {
    return NULL;
  }

  /* Otherwise, emulate calloc */
  void *mem = aws_mem_acquire(allocator, required_bytes);
  if (!mem) {
    aws_raise_error(AWS_ERROR_OOM);
    return NULL;
  }
  memset(mem, 0, required_bytes);
  return mem;
}

void aws_mem_release(struct aws_allocator *allocator, void *ptr) {
  (void)allocator;
  if (ptr != NULL) {
    free(ptr);
  }
}

int aws_mem_realloc(struct aws_allocator *allocator, void **ptr, size_t oldsize,
                    size_t newsize) {
  (void)allocator;
  if (newsize == 0) {
    aws_mem_release(allocator, *ptr);
    *ptr = NULL;
    return AWS_OP_SUCCESS;
  }

  /* Since the allocator doesn't support realloc, we'll need to emulate it
   * (inefficiently). */
  if (oldsize >= newsize) {
    return AWS_OP_SUCCESS;
  }

  void *newptr = aws_mem_acquire(allocator, newsize);
  if (!newptr) {
    return aws_raise_error(AWS_ERROR_OOM);
  }

  memcpy(newptr, *ptr, oldsize);
  memset((uint8_t *)newptr + oldsize, 0, newsize - oldsize);

  aws_mem_release(allocator, *ptr);

  *ptr = newptr;

  return AWS_OP_SUCCESS;
}

/**
 * This assert will fail if code ever uses a different allocator than expected
 * during a proof
 */
bool aws_allocator_is_valid(const struct aws_allocator *alloc) {
  return alloc == sea_allocator();
}
