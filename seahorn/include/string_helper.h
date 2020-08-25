#pragma once

#include <aws/common/string.h>

struct aws_string *ensure_string_is_allocated(size_t len);
struct aws_string *ensure_string_is_allocated_bounded_length(size_t max_size);
