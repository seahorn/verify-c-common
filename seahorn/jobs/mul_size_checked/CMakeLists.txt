add_executable(mul_size_checked
  aws_mul_size_checked_harness.c)
sea_attach_bc_link(mul_size_checked)
sea_add_unsat_test(mul_size_checked)

# klee
sea_add_klee(mul_size_checked
aws_mul_size_checked_harness.c)

sea_add_fuzz(mul_size_checked aws_mul_size_checked_harness.c)
