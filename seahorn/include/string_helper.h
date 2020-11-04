#pragma once

#include <aws/common/string.h>

struct aws_string *ensure_string_is_allocated(size_t len);
struct aws_string *ensure_string_is_allocated_nondet_length(void);
struct aws_string *ensure_string_is_allocated_bounded_length(size_t max_size);

void sea_init_str(const char *str, size_t len);

// len is populated by this function
const char *ensure_c_str_is_nd_allocated_safe(size_t max_size, size_t *len);
const char *ensure_c_str_is_nd_allocated(size_t max_size, size_t *len);

const char *ensure_c_str_is_allocated(size_t max_size);
