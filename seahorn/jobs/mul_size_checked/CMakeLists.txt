add_executable(mul_size_checked
  aws_mul_size_checked_harness.c
  ${SEA_LIB}/utils.c)
sea_attach_bc(mul_size_checked)
sea_add_unsat_test(mul_size_checked)
