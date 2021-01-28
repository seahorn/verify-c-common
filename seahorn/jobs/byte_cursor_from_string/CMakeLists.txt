add_executable(byte_cursor_from_string
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  ${AWS_C_COMMON_ROOT}/source/string.c
  aws_byte_cursor_from_string_harness.c)
sea_attach_bc_link(byte_cursor_from_string)
configure_file(sea.yaml sea.yaml @ONLY)
sea_add_unsat_test(byte_cursor_from_string)

# klee
sea_add_klee(byte_cursor_from_string
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  ${AWS_C_COMMON_ROOT}/source/string.c
  aws_byte_cursor_from_string_harness.c)

sea_add_fuzz(byte_cursor_from_string
  aws_byte_cursor_from_string_harness.c)
