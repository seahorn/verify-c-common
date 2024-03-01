#include <bounds.h>
#include <seahorn/seahorn.h>

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#define INLINE __attribute__((always_inline))
/**
  The bcmp() function compares the two byte sequences s1 and s2 of
  length n each.  If they are equal, and in particular if n is zero,
  bcmp() returns 0.  Otherwise, it returns a nonzero result.
*/
INLINE int bcmp(const void *s1, const void *s2, size_t n) {
  size_t i;

  size_t max_buffer_size = sea_max_buffer_size();
  const uint8_t *p1;
  const uint8_t *p2;
  p1 = s1;
  p2 = s2;

  if (p1 == p2)
    return 0;
  if (p1 == NULL || p2 == NULL)
    return 1;
  /* pre-unroll the loop for MAX_BUFFER_SIZE */
  for (i = 0; i < max_buffer_size; i++) {
    if (i < n) {
      if (p1[i] != p2[i]) {
        return 1;
      }
    }
  }
  /* unroll the rest, if any */
  for (i = max_buffer_size; i < n; i++) {
    if (p1[i] != p2[i])
      return 1;
  }

  return 0;
}

INLINE int memcmp(const void *s1, const void *s2, size_t n) {
  size_t i;
  size_t max_buffer_size = sea_max_buffer_size();

  const uint8_t *p1;
  const uint8_t *p2;
  p1 = s1;
  p2 = s2;

  if (p1 == p2)
    return 0;

  /* pre-unroll the loop for MAX_BUFFER_SIZE */
  for (i = 0; i < max_buffer_size; i++) {
    if (i < n) {
      if (p1[i] != p2[i]) {
        return p1[i] < p2[i] ? -1 : 1;
      }
    }
  }
  /* unroll the rest, if any */
  for (i = max_buffer_size; i < n; i++) {
    if (p1[i] != p2[i])
      return p1[i] < p2[i] ? -1 : 1;
  }

  return 0;
}

INLINE void *__memcpy_chk(void *dest, const void *src, size_t len,
                          size_t dstlen) {
  sassert(!(dstlen < len));
  return __builtin_memcpy(dest, src, len);
}

INLINE void *__memset_chk(void *dest, int c, size_t len, size_t dstlen) {
  sassert(!(dstlen < len));
  return __builtin_memset(dest, c, len);
}

/* on OSX memmove is a macro */
#ifndef memmove
#ifdef __SYMBIOTIC__
INLINE void *memmove(void *to, const void *from, size_t n)
{
	unsigned long rem, chunks, tmp1, tmp2;
	unsigned char *tmp_to;
	unsigned char *tmp_from = (unsigned char *)from;

	if (tmp_from >= (unsigned char *)to)
		return memcpy(to, from, n);
	chunks = n / 8;
	tmp_from += n;
	tmp_to = to + n;
	if (!chunks)
		goto lessthan8;
	rem = (unsigned long )tmp_to % 4;
	if (rem)
		goto align;
 copy_chunks:
	do {
		/* make gcc to load all data, then store it */
		tmp1 = *(unsigned long *)(tmp_from-4);
		tmp_from -= 8;
		tmp2 = *(unsigned long *)tmp_from;
		*(unsigned long *)(tmp_to-4) = tmp1;
		tmp_to -= 8;
		*(unsigned long *)tmp_to = tmp2;
	} while (--chunks);
 lessthan8:
	n = n % 8;
	if (n >= 4) {
		*(unsigned long *)(tmp_to-4) = *(unsigned long *)(tmp_from-4);
		tmp_from -= 4;
		tmp_to -= 4;
		n = n-4;
	}
	if (!n ) return to;
	do {
		*--tmp_to = *--tmp_from;
	} while (--n);
	
	return to;
 align:
	rem = 4 - rem;
	n = n - rem;
	do {
		*--tmp_to = *--tmp_from;
	} while (--rem);
	chunks = n / 8;
	if (chunks)
		goto copy_chunks;
	goto lessthan8;
}
#else
INLINE void* memmove(void *dst, const void *src, size_t len)  {
  sassert(sea_is_dereferenceable(dst, len));
  sassert(sea_is_dereferenceable(src, len));
  return __builtin_memmove(dst, src, len);
}
#endif
#endif

/* on OSX memcpy is a macro */
#ifndef memcpy
#ifdef __SYMBIOTIC__
INLINE void *memcpy(void *dest, void const *from, size_t n) {
  char const *ifrom = from;
  char *idest = dest;
  while (n--)
    *idest++ = *ifrom++;
  return dest;
}
#else
INLINE void *memcpy(void *dst, const void *src, size_t len) {
  sassert(sea_is_dereferenceable(dst, len));
  sassert(sea_is_dereferenceable(src, len));
  return __builtin_memcpy(dst, src, len);
}
#endif
#endif

#ifdef __SYMBIOTIC__
#ifndef memset
INLINE void *memset(void * dst, int s, size_t count) {
  char * a = dst;
  while (count-- > 0)
    *a++ = s;
  return dst;
}
#endif
#endif

INLINE void *memchr(const void *str, int c, size_t n) {
  sassert(sea_is_dereferenceable(str, n));
  return __builtin_memchr(str, c, n);
}

INLINE int strncmp(const char *str1, const char *str2, size_t n) {
    for (size_t i = 0; i < n; i++) {
        if (str1[i] == '\0' || str2[i] == '\0') {
            return memcmp(str1, str2, i);
        }
    }
    return memcmp(str1, str2, n);
}