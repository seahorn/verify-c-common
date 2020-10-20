add_executable(add_size_checked
  aws_add_size_checked_harness.c
  ${SEA_LIB}/error.c)
sea_attach_bc(add_size_checked)
sea_add_unsat_test(add_size_checked)

sea_attach_fuzz(add_size_checked)
