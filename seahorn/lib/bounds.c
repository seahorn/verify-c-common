#include <bounds.h>

#ifndef MAX_BUFFER_SIZE
#define MAX_BUFFER_SIZE 10
#endif

#ifndef MAX_STRING_LEN
#define MAX_STRING_LEN MAX_BUFFER_SIZE
#endif

#ifndef MAX_ITEM_SIZE
#define MAX_ITEM_SIZE 2
#endif

#ifndef MAX_INITIAL_SIZE
#define MAX_INITIAL_SIZE MAX_BUFFER_SIZE
#endif

#ifndef MAX_INITIAL_ITEM_ALLOCATION
#define MAX_INITIAL_ITEM_ALLOCATION 9223372036854775808ULL
#endif

#ifndef MAX_TABLE_SIZE
#define MAX_TABLE_SIZE 4
#endif

size_t sea_max_buffer_size(void) { return MAX_BUFFER_SIZE; }
size_t sea_max_string_len(void) { return MAX_STRING_LEN; }
size_t sea_max_array_list_initial_size(void) { return MAX_INITIAL_SIZE; }
size_t sea_max_array_list_item_size(void) { return MAX_ITEM_SIZE; }
size_t sea_max_array_list_len(void) { return MAX_INITIAL_ITEM_ALLOCATION; }
size_t sea_MAX_TABLE_SIZE(void) { return MAX_TABLE_SIZE; }