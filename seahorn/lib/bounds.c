#include <bounds.h>

#ifndef MAX_BUFFER_SIZE
#define MAX_BUFFER_SIZE 10
#endif

#ifndef MAX_STRING_LEN
#define MAX_STRING_LEN MAX_BUFFER_SZIE
#endif

size_t sea_max_buffer_size(void) { return MAX_BUFFER_SIZE; }
size_t sea_max_string_len(void) { return MAX_STRING_LEN; }
