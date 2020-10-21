/** Definitions of nd() functions for fuzzing */

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include <setjmp.h>

/** Global access to fuzz data */
uint8_t *g_fuzz_data;
size_t g_fuzz_data_size;
uint8_t *g_fuzz_data_iterator;

/** jmp environment */
jmp_buf g_jmp_buf;

#define UPDATE_FUZZ_ITERATOR(TYPE)                                             \
  if (g_fuzz_data_iterator + sizeof(TYPE) - g_fuzz_data >= g_fuzz_data_size) { \
    g_fuzz_data_iterator = g_fuzz_data;                                        \
  }

bool nd_bool(void) {
  bool res;

  UPDATE_FUZZ_ITERATOR(bool)
  memcpy(&res, g_fuzz_data_iterator, sizeof(bool));
  g_fuzz_data_iterator += sizeof(bool);

  return res;
}

uint32_t nd_uint32_t(void) {
  uint32_t res;

  UPDATE_FUZZ_ITERATOR(uint32_t);
  memcpy(&res, g_fuzz_data_iterator, sizeof(uint32_t));
  g_fuzz_data_iterator += sizeof(uint32_t);

  return res;
}

uint64_t nd_uint64_t(void) {
  uint64_t res;

  UPDATE_FUZZ_ITERATOR(uint64_t);
  memcpy(&res, g_fuzz_data_iterator, sizeof(uint64_t));
  g_fuzz_data_iterator += sizeof(uint64_t);

  return res;
}

void __VERIFIER_assert(bool v) {
  /* fprintf(stdout, "CHECK ASSERT\n"); */
  fflush(stdout);

  return assert(v);
}

void __VERIFIER_assume(bool v) {
  // -- if assumption fails, jump back to LLVMFuzzerTestOneInput
  if (!v) {
    longjmp(g_jmp_buf, 1);
  }
}

void __VERIFIER_error(void) {
  fprintf(stdout, "ERROR REACHED\n");
  fflush(stdout);
  assert(0);
}

/** expected entry of verification harness */
extern int _main(void);

int LLVMFuzzerTestOneInput(uint8_t *Data, size_t Size) {
  g_fuzz_data = Data;
  g_fuzz_data_size = Size;
  g_fuzz_data_iterator = g_fuzz_data;

  if (setjmp(g_jmp_buf)) {
    // assumption failed, abort
    return 0;
  }
  _main();

  return 0;
}
