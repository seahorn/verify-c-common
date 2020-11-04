#include <seahorn/seahorn.h>
#include <sea_string.h>

#include <bounds.h>
#include <nondet.h>

#ifdef __SEAHORN__
size_t strlen(const char *str) { return sea_strlen(str, sea_max_string_len()); }
#endif

// A strlen implementation.
// If the end-delimiter is not in offset <= max_size from start then
// 0 is returned.
size_t sea_strlen(const char *str, size_t max_size) {
  size_t len = 0;

  size_t max_string_len = sea_max_string_len();
  for (size_t i = 0; i < max_string_len; i++) {
    if (i <= max_size) {
      if (str[i] == '\0') {
        return len;
      }
      len++;
    }
  }
  return 0;
}

// This function is here for posterity only.
// Similar to `sea_strlen` it returns the length of a string
// but most importantly it creates a valid string of that length
// pointed to by `str`.
// OTOH `sea_strlen` is close to a conventional `strlen` and does not write to
// the string.
size_t sea_strlen_unused(const char *str, size_t max) {
  size_t i;
  i = nd_size_t();
  size_t max_string_len = sea_max_string_len();
  assume(i < max && max <= max_string_len);
  assume(str[i] == '\0');
  // The following assumption cannot be expressed
  // assume(forall j :: j < i ==> str[j] != '\0');
  // therefore, we say the following:
  size_t j = 0;
  for (j = 0; j < max_string_len; j++) {
    if (j < i) {
      assume(str[j] != '\0');
    }
  }
  return i;
}
