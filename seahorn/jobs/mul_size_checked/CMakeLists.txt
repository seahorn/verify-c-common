add_executable(mul_size_checked
  aws_mul_size_checked_harness.c
  ${SEA_LIB}/utils.c)
# XXX MAX_BUFFER_SIZE is needed for utils.c
# XXX refactor utils.c to avoid this
target_compile_definitions(mul_size_checked PUBLIC MAX_BUFFER_SIZE=10)
sea_attach_bc(mul_size_checked)
sea_add_unsat_test(mul_size_checked)
