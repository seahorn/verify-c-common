#include <bounds.h>
#include <config.h>

size_t sea_max_buffer_size(void) { return MAX_BUFFER_SIZE; }
size_t sea_max_string_len(void) { return MAX_STRING_LEN; }
size_t klee_max_memory_size(void) { return KLEE_MAX_SIZE; }
size_t sea_max_array_list_item_size(void) { return MAX_ITEM_SIZE; }
size_t sea_max_array_list_len(void) { return MAX_INITIAL_ITEM_ALLOCATION; }
size_t fuzz_max_array_list_len(void) { return MAX_INITIAL_ITEM_ALLOCATION_FUZZ; }
size_t fuzz_max_array_list_item_size(void) { return MAX_ITEM_SIZE_FUZZ; }
size_t sea_max_table_size(void) { return MAX_TABLE_SIZE; }
size_t crab_max_array_size(void) { return MAX_ARRAY_SIZE; }