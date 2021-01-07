/**
 */

#include <stddef.h>

#include <aws/common/hash_table.h>
#include <aws/common/string.h>

#include <seahorn/seahorn.h>

#include <proof_allocators.h>
#include <string_helper.h>
#include <utils.h>

extern NONDET_FN_ATTR int nd_int_strcmp(void);
// -- strcmp up to MAX_STRING_LEN, and non-deterministic result otherwise
int strcmp(const char *str1, const char *str2) {

  const unsigned char *s1 = (const unsigned char*)str1;
  const unsigned char *s2 = (const unsigned char*)str2;

  unsigned char c1, c2;
  for (unsigned i = 0; i < MAX_STRING_LEN; ++i) {
    c1 = *s1++;
    c2 = *s2++;
    if (c1 == '\0' && c2 == '\0') return 0;
    if (c1 != c2) return c1 - c2;
  }
  return nd_int_strcmp();
}

int main(void) {
  size_t str1_len;
  size_t str2_len;
  const char *str1 = ensure_c_str_is_nd_allocated(MAX_STRING_LEN, &str1_len);
  const char *str2 =
      nd_bool() ? str1
                : ensure_c_str_is_nd_allocated(MAX_STRING_LEN, &str2_len);

  assume(aws_c_string_is_valid(str1));
  assume(aws_c_string_is_valid(str2));

  bool rval = aws_hash_callback_c_str_eq(str1, str2);
  if (rval) {
    size_t len = strlen(str1);
    assert_bytes_match((const unsigned char *)str1, (const unsigned char *)str2,
                       len);
  }
  return 0;
}
