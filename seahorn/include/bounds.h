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

SEAHORN_EXTERN_C_END
