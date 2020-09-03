add_executable(ptr_eq
  ${AWS_C_COMMON_ROOT}/source/hash_table.c
  aws_ptr_eq_harness.c)
sea_attach_bc(ptr_eq)
sea_add_unsat_test(ptr_eq)
