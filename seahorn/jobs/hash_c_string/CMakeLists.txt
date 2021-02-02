add_executable(hash_c_string
  ${AWS_C_COMMON_ROOT}/source/hash_table.c
  aws_hash_c_string_harness.c)
sea_attach_bc_link(hash_c_string)
sea_add_unsat_test(hash_c_string)

# klee
sea_add_klee(hash_c_string
  ${AWS_C_COMMON_ROOT}/source/hash_table.c
  aws_hash_c_string_harness.c)