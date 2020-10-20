#ifndef aws_raise_error_private
void aws_raise_error_private(int err) {
#ifdef AWS_ERROR_IS_VERIFIER_ERROR
  __VERIFIER_error();
#elif AWS_ERROR_IS_EXIT
  exit(1)
#else
  return;
#endif
}
#endif
