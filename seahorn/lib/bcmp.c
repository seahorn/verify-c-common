#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <strings.h>

#include <seahorn/seahorn.h>

#ifndef MAX_BUFFER_SIZE
#error "MAX_BUFFER_SIZE must be defined, try 16"
#define MAX_BUFFER_SIZE 16
#endif
/**
  The bcmp() function compares the two byte sequences s1 and s2 of
  length n each.  If they are equal, and in particular if n is zero,
  bcmp() returns 0.  Otherwise, it returns a nonzero result.
*/
__attribute__((always_inline)) int bcmp(const void *s1, const void *s2,
                                        size_t n) {
  size_t i;

  const uint8_t *p1;
  const uint8_t *p2;
  p1 = s1;
  p2 = s2;

  if (p1 == p2)
    return 0;
  if (p1 == NULL || p2 == NULL)
    return 1;
  /* pre-unroll the loop for MAX_BUFFER_SIZE */
  for (i = 0; i < MAX_BUFFER_SIZE; i++) {
    if (i < n) {
      if (p1[i] != p2[i]) {
        return 1;
      }
    }
  }
  /* unroll the rest, if any */
  for (i = MAX_BUFFER_SIZE; i < n; i++) {
    if (p1[i] != p2[i])
      return 1;
  }

  return 0;
}

__attribute__((always_inline)) int memcmp(const void *s1, const void *s2,
                                          size_t n) {
  size_t i;

  const uint8_t *p1;
  const uint8_t *p2;
  p1 = s1;
  p2 = s2;

  if (p1 == p2)
    return 0;

  /* pre-unroll the loop for MAX_BUFFER_SIZE */
  for (i = 0; i < MAX_BUFFER_SIZE; i++) {
    if (i < n) {
      if (p1[i] != p2[i]) {
        return p1[i] < p2[i] ? -1 : 1;
      }
    }
  }
  /* unroll the rest, if any */
  for (i = MAX_BUFFER_SIZE; i < n; i++) {
    if (p1[i] != p2[i])
      return p1[i] < p2[i] ? -1 : 1;
  }

  return 0;
}

__attribute__((always_inline)) void *
__memcpy_chk(void *dest, const void *src, size_t len, size_t dstlen) {
  sassert(!(dstlen < len));
  return __builtin_memcpy(dest, src, len);
}
