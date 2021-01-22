add_executable(string_eq_byte_cursor
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  ${AWS_C_COMMON_ROOT}/source/string.c
  ${AWS_C_COMMON_ROOT}/source/common.c
  aws_string_eq_byte_cursor_harness.c)
sea_attach_bc_link(string_eq_byte_cursor)
sea_add_unsat_test(string_eq_byte_cursor)

# klee
sea_add_klee(string_eq_byte_cursor
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  ${AWS_C_COMMON_ROOT}/source/string.c
  ${AWS_C_COMMON_ROOT}/source/common.c
  aws_string_eq_byte_cursor_harness.c)