add_executable(
  string_eq_byte_cursor
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  ${AWS_C_COMMON_ROOT}/source/string.c
  ${AWS_C_COMMON_ROOT}/source/common.c
  aws_string_eq_byte_cursor_harness.c
)
sea_attach_bc_link(string_eq_byte_cursor)
sea_add_unsat_test(string_eq_byte_cursor)

# klee
sea_add_klee(
  string_eq_byte_cursor
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  ${AWS_C_COMMON_ROOT}/source/string.c
  ${AWS_C_COMMON_ROOT}/source/common.c
  aws_string_eq_byte_cursor_harness.c
)

# fuzz
sea_add_fuzz(
  string_eq_byte_cursor
  aws_string_eq_byte_cursor_harness.c
)

# smack
if(SEA_ENABLE_SMACK)
  sea_add_smack_bc(string_eq_byte_cursor
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  ${AWS_C_COMMON_ROOT}/source/string.c
  ${AWS_C_COMMON_ROOT}/source/common.c
  aws_string_eq_byte_cursor_harness.c)
  sea_add_smack_test(string_eq_byte_cursor --strings)
endif()