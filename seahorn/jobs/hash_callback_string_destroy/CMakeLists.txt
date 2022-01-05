add_executable(hash_callback_string_destroy
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  ${AWS_C_COMMON_ROOT}/source/string.c
  ${AWS_C_COMMON_ROOT}/source/hash_table.c
  ${AWS_C_COMMON_ROOT}/source/common.c
  aws_hash_callback_string_destroy_harness.c)
sea_attach_bc_link(hash_callback_string_destroy)
sea_add_unsat_test(hash_callback_string_destroy)

# klee
sea_add_klee(hash_callback_string_destroy
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  ${AWS_C_COMMON_ROOT}/source/string.c
  ${AWS_C_COMMON_ROOT}/source/common.c
  ${AWS_C_COMMON_ROOT}/source/hash_table.c
  aws_hash_callback_string_destroy_harness.c)

# fuzz
sea_add_fuzz(hash_callback_string_destroy
  aws_hash_callback_string_destroy_harness.c)

# smack
sea_add_smack(hash_callback_string_destroy
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  ${AWS_C_COMMON_ROOT}/source/string.c
  ${AWS_C_COMMON_ROOT}/source/common.c
  ${AWS_C_COMMON_ROOT}/source/hash_table.c
  aws_hash_callback_string_destroy_harness.c)

# symbiotic
sea_add_symbiotic(hash_callback_string_destroy
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  ${AWS_C_COMMON_ROOT}/source/string.c
  ${AWS_C_COMMON_ROOT}/source/common.c
  ${AWS_C_COMMON_ROOT}/source/hash_table.c
  aws_hash_callback_string_destroy_harness.c)