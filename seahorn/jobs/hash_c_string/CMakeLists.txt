add_executable(hash_c_string
  ${AWS_C_COMMON_ROOT}/source/hash_table.c
  aws_hash_c_string_harness.c)
sea_attach_bc_link(hash_c_string)
sea_add_unsat_test(hash_c_string)

# klee
sea_add_klee(hash_c_string
  ${AWS_C_COMMON_ROOT}/source/hash_table.c
  aws_hash_c_string_harness.c)

# smack
sea_add_smack(hash_c_string
  ${AWS_C_COMMON_ROOT}/source/hash_table.c
  aws_hash_c_string_harness.c)

# symbiotic
sea_add_symbiotic(hash_c_string
  ${AWS_C_COMMON_ROOT}/source/hash_table.c
  aws_hash_c_string_harness.c)