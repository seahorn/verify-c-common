add_executable(hash_string
  ${AWS_C_COMMON_ROOT}/source/string.c
  ${AWS_C_COMMON_ROOT}/source/hash_table.c
  aws_hash_string_harness.c)
sea_attach_bc_link(hash_string)
sea_add_unsat_test(hash_string)

# klee
sea_add_klee(hash_string
  ${AWS_C_COMMON_ROOT}/source/string.c
  ${AWS_C_COMMON_ROOT}/source/hash_table.c
  aws_hash_string_harness.c)

# fuzz
sea_add_fuzz(hash_string aws_hash_string_harness.c)

# smack
sea_add_smack(hash_string
  ${AWS_C_COMMON_ROOT}/source/string.c
  ${AWS_C_COMMON_ROOT}/source/hash_table.c
  aws_hash_string_harness.c)

# symbiotic
sea_add_symbiotic(hash_string
  ${AWS_C_COMMON_ROOT}/source/string.c
  ${AWS_C_COMMON_ROOT}/source/hash_table.c
  aws_hash_string_harness.c)