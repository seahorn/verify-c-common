add_executable(
  string_compare
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  ${AWS_C_COMMON_ROOT}/source/string.c
  ${AWS_C_COMMON_ROOT}/source/common.c
  aws_string_compare_harness.c
)
sea_attach_bc_link(string_compare)
sea_add_unsat_test(string_compare)

# klee
sea_add_klee(
  string_compare
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  ${AWS_C_COMMON_ROOT}/source/string.c
  ${AWS_C_COMMON_ROOT}/source/common.c
  aws_string_compare_harness.c
)

# fuzz
sea_add_fuzz(
  string_compare
  aws_string_compare_harness.c
)

# smack
if(SEA_ENABLE_SMACK)
  sea_add_smack_bc(string_compare
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  ${AWS_C_COMMON_ROOT}/source/string.c
  ${AWS_C_COMMON_ROOT}/source/common.c
  aws_string_compare_harness.c)
  sea_add_smack_test(string_compare --strings)
endif()

# symbiotic
sea_add_symbiotic(
  string_compare
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  ${AWS_C_COMMON_ROOT}/source/string.c
  ${AWS_C_COMMON_ROOT}/source/common.c
  aws_string_compare_harness.c
)