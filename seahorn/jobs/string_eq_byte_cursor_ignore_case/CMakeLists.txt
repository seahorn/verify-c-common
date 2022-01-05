add_executable(
  string_eq_byte_cursor_ignore_case
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  ${AWS_C_COMMON_ROOT}/source/string.c
  ${AWS_C_COMMON_ROOT}/source/common.c
  aws_string_eq_byte_cursor_ignore_case_harness.c
)
sea_attach_bc_link(string_eq_byte_cursor_ignore_case)
configure_file(sea.yaml sea.yaml @ONLY)
sea_add_unsat_test(string_eq_byte_cursor_ignore_case)

# klee
sea_add_klee(
  string_eq_byte_cursor_ignore_case
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  ${AWS_C_COMMON_ROOT}/source/string.c
  ${AWS_C_COMMON_ROOT}/source/common.c
  aws_string_eq_byte_cursor_ignore_case_harness.c
)

# fuzz
sea_add_fuzz(
  string_eq_byte_cursor_ignore_case
  aws_string_eq_byte_cursor_ignore_case_harness.c
)

# smack
sea_add_smack(
  string_eq_byte_cursor_ignore_case
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  ${AWS_C_COMMON_ROOT}/source/string.c
  ${AWS_C_COMMON_ROOT}/source/common.c
  aws_string_eq_byte_cursor_ignore_case_harness.c
)

# symbiotic
sea_add_symbiotic(
  string_eq_byte_cursor_ignore_case
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  ${AWS_C_COMMON_ROOT}/source/string.c
  ${AWS_C_COMMON_ROOT}/source/common.c
  aws_string_eq_byte_cursor_ignore_case_harness.c
)