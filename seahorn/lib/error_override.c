#include <aws/common/common.h>

static AWS_THREAD_LOCAL int tl_last_error = 0;

void aws_raise_error_private(int err) {
  tl_last_error = err;
}

int aws_last_error(void) {
  return tl_last_error;
}