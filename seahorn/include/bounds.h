#pragma once

#include <macros.h>
#include <stddef.h>

SEAHORN_EXTERN_C_BEGIN

/**
   Returns the current upper bound on buffer size
 */
size_t sea_max_buffer_size(void);

/**
   Returns the current upper bound on string size
 */
size_t sea_max_string_len(void);

/**
   Returns the current upper bound on memory allocation size for klee
 */
size_t klee_max_memory_size(void);

/**
   Returns the current upper bound on array list item size
 */
size_t sea_max_array_list_item_size(void);

/**
   Returns the current upper bound on array list length
 */
size_t sea_max_array_list_len(void);

/**
   Returns the current upper bound on array list item size for fuzzing
 */
size_t fuzz_max_array_list_item_size(void);

/**
   Returns the current upper bound on array list length for fuzzing
 */
size_t fuzz_max_array_list_len(void);

SEAHORN_EXTERN_C_END
