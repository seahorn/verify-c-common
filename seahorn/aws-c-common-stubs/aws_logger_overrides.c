
#include <aws/common/logging.h>

struct aws_logger s_null_logger = {
    .vtable = NULL,
    .allocator = NULL,
    .p_impl = NULL,
};

struct aws_logger *aws_logger_get(void) {
    return &s_null_logger;
}