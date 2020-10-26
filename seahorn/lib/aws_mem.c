/** Custom version of aws_mem functions */

/************************************************************************************************************/

void *aws_mem_acquire(struct aws_allocator *allocator, size_t size) {
  AWS_FATAL_PRECONDITION(aws_allocator_is_valid(allocator));
  /* Protect against
   * https://wiki.sei.cmu.edu/confluence/display/c/MEM04-C.+Beware+of+zero-length+allocations
   */
  AWS_FATAL_PRECONDITION(size != 0);

  void *mem = can_fail_malloc(size);
  if (!mem) {
    aws_raise_error(AWS_ERROR_OOM);
  }
  return mem;
}

void *aws_mem_calloc(struct aws_allocator *allocator, size_t num, size_t size) {
  AWS_FATAL_PRECONDITION(aws_allocator_is_valid(allocator));
  /* Protect against
   * https://wiki.sei.cmu.edu/confluence/display/c/MEM04-C.+Beware+of+zero-length+allocations
   */
  AWS_FATAL_PRECONDITION(num != 0 && size != 0);

  /* Defensive check: never use calloc with size * num that would overflow
   * https://wiki.sei.cmu.edu/confluence/display/c/MEM07-C.+Ensure+that+the+arguments+to+calloc%28%29%2C+when+multiplied%2C+do+not+wrap
   */
  size_t required_bytes;
  if (aws_mul_size_checked(num, size, &required_bytes)) {
    return NULL;
  }

  void *mem = bounded_calloc(num, size);
  if (!mem) {
    aws_raise_error(AWS_ERROR_OOM);
  }
  return mem;
}

#define AWS_ALIGN_ROUND_UP(value, alignment)                                   \
  (((value) + ((alignment)-1)) & ~((alignment)-1))

void *aws_mem_acquire_many(struct aws_allocator *allocator, size_t count, ...) {

  enum { S_ALIGNMENT = sizeof(intmax_t) };

  va_list args_size;
  va_start(args_size, count);
  va_list args_allocs;
  va_copy(args_allocs, args_size);

  size_t total_size = 0;
  for (size_t i = 0; i < count; ++i) {

    /* Ignore the pointer argument for now */
    va_arg(args_size, void **);

    size_t alloc_size = va_arg(args_size, size_t);
    total_size += AWS_ALIGN_ROUND_UP(alloc_size, S_ALIGNMENT);
  }
  va_end(args_size);

  void *allocation = NULL;

  if (total_size > 0) {

    allocation = bounded_malloc(total_size);
    if (!allocation) {
      aws_raise_error(AWS_ERROR_OOM);
      goto cleanup;
    }

    uint8_t *current_ptr = allocation;

    for (size_t i = 0; i < count; ++i) {

      void **out_ptr = va_arg(args_allocs, void **);

      size_t alloc_size = va_arg(args_allocs, size_t);
      alloc_size = AWS_ALIGN_ROUND_UP(alloc_size, S_ALIGNMENT);

      *out_ptr = current_ptr;
      current_ptr += alloc_size;
    }
  }

cleanup:
  va_end(args_allocs);
  return allocation;
}

#undef AWS_ALIGN_ROUND_UP

void aws_mem_release(struct aws_allocator *allocator, void *ptr) {
  AWS_FATAL_PRECONDITION(allocator != NULL);
  if (ptr != NULL) {
    free(ptr);
  }
}

int aws_mem_realloc(struct aws_allocator *allocator, void **ptr, size_t oldsize,
                    size_t newsize) {
  AWS_FATAL_PRECONDITION(allocator != NULL);

  /* Protect against
   * https://wiki.sei.cmu.edu/confluence/display/c/MEM04-C.+Beware+of+zero-length+allocations
   */
  if (newsize == 0) {
    aws_mem_release(allocator, *ptr);
    *ptr = NULL;
    return AWS_OP_SUCCESS;
  }

  void *newptr = realloc(*ptr, newsize);
  if (!newptr) {
    return aws_raise_error(AWS_ERROR_OOM);
  }
  *ptr = newptr;
  return AWS_OP_SUCCESS;
}

/**
 * This assert will fail if code ever uses a different allocator than expected
 * during a proof
 */
bool aws_allocator_is_valid(const struct aws_allocator *alloc) {
  return alloc == _allocator();
}
