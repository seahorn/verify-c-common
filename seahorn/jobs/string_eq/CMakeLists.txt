add_executable(
  string_eq
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  ${AWS_C_COMMON_ROOT}/source/string.c
  ${AWS_C_COMMON_ROOT}/source/common.c
  aws_string_eq_harness.c
)
sea_attach_bc_link(string_eq)
sea_add_unsat_test(string_eq)

# klee
sea_add_klee(
  string_eq
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  ${AWS_C_COMMON_ROOT}/source/string.c
  ${AWS_C_COMMON_ROOT}/source/common.c
  aws_string_eq_harness.c
)

# fuzz
sea_add_fuzz(
  string_eq
  aws_string_eq_harness.c
)

# smack
if(SEA_ENABLE_SMACK)
  sea_add_smack_bc(string_eq
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  ${AWS_C_COMMON_ROOT}/source/string.c
  ${AWS_C_COMMON_ROOT}/source/common.c
  aws_string_eq_harness.c)
  sea_add_smack_test(string_eq --strings)
endif()

# symbiotic
sea_add_symbiotic(
  string_eq
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  ${AWS_C_COMMON_ROOT}/source/string.c
  ${AWS_C_COMMON_ROOT}/source/common.c
  aws_string_eq_harness.c
)