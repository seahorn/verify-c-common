
static int tl_last_error = 0;

void aws_raise_error_private(int err) {
  tl_last_error = err;
  #ifdef AWS_ERROR_IS_VERIFIER_ERROR
    __VERIFIER_error();
  #elif AWS_ERROR_IS_EXIT
    exit(1)
  #else
    return;
  #endif
}

int aws_last_error(void) {
    return tl_last_error;
}