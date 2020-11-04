/** Different memory allocators*/
#pragma once
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#define INLINE __attribute__((always_inline))

/**
   Basic memory allocator to be used instead of malloc()

   Same semantics as malloc(). Can non-deterministically return NULL to indicate
   allocation failure.
 */
INLINE void *sea_malloc(size_t sz);

/**
   Aligned memory allocator

   Same as sea_malloc() but rounds the allocation size up to the nearest word
*/
INLINE void *sea_malloc_aligned(size_t sz);

/**
   Initializing memory allcator

   Same as malloc() but initializes memory non-deterministically
 */
INLINE void *sea_malloc_havoc(size_t sz);

/**
   Non-failing memory allocator

   Same as malloc() but guarantees that allocation does not fail
 */
INLINE void *sea_malloc_safe(size_t sz);

/**
   Non-failing initializing allocator

   Combination of sea_malloc_havoc() with sea_malloc_safe()
 */
INLINE void *sea_malloc_havoc_safe(size_t sz);

/**
   Non-failing aligned allocator

   Combination of sea_malloc_safe() with sea_malloc_aligned()
 */
INLINE void *sea_malloc_aligned_safe(size_t sz);

/**
   Initializing aligned allocator

   Combination of sea_malloc_havoc() with sea_malloc_aligned()
 */
INLINE void *sea_malloc_aligned_havoc(size_t sz);

INLINE void sea_free(void *ptr);
INLINE void *sea_realloc(void *ptr, size_t sz);
