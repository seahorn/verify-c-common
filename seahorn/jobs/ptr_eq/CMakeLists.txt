add_executable(ptr_eq
  ${AWS_C_COMMON_ROOT}/source/hash_table.c
  aws_ptr_eq_harness.c)
sea_attach_bc_link(ptr_eq)
sea_add_unsat_test(ptr_eq)

# klee
sea_add_klee(ptr_eq
  ${AWS_C_COMMON_ROOT}/source/hash_table.c
  aws_ptr_eq_harness.c)

# smack
sea_add_smack(ptr_eq
  ${AWS_C_COMMON_ROOT}/source/hash_table.c
  aws_ptr_eq_harness.c)

# symbiotic
# sea_add_symbiotic(ptr_eq
#   ${AWS_C_COMMON_ROOT}/source/hash_table.c
#   aws_ptr_eq_harness.c)