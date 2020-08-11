#include <stddef.h>
#include <stdint.h>
#include <strings.h>

/**
  The bcmp() function compares the two byte sequences s1 and s2 of
  length n each.  If they are equal, and in particular if n is zero,
  bcmp() returns 0.  Otherwise, it returns a nonzero result.
*/
int bcmp(const void *s1, const void *s2, size_t n) {
  size_t i;

  const uint8_t *p1;
  const uint8_t *p2;
  p1 = s1;
  p2 = s2;

  if (p1 == p2) return 0;
  if (p1 == NULL || p2 == NULL) return 1;
  for (i = 0; i < n; i++) {
    if (p1[i] != p2[i])
      return 1;
  }

  return 0;
}
