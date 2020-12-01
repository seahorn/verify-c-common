#include <bounds.h>
#include <macros.h>
#include <nondet.h>
#include <sea_string.h>
#include <seahorn/seahorn.h>

template <size_t i, size_t N, typename Function> class Loop {
public:
  static size_t call(Function f, const char *str) {
    bool r = f(i, N, str);
    if (r)
      return i;
    return Loop<i + 1, N, Function>::call(f, str);
  }
};

template <size_t N, typename Function> class Loop<N, N, Function> {
public:
  static size_t call(Function f, const char *str) {
    (void)f;
    return N;
  }
};

SEAHORN_EXTERN_C_BEGIN

#ifdef __SEAHORN__
size_t strlen(const char *str) { return sea_strlen(str, sea_max_string_len()); }
#endif

bool isEOF(int i, int N, const char *str) { return str[i] == '\0'; }

size_t sea_strlen(const char *str, size_t max_size) {
  size_t size = Loop<0, MAX_STRING_LEN, decltype(isEOF)>::call(isEOF, str);
  return size <= max_size ? size : 0;
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

SEAHORN_EXTERN_C_END