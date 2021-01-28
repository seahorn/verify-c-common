add_executable(byte_cursor_from_c_str
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  aws_byte_cursor_from_c_str_harness.c)
sea_attach_bc_link(byte_cursor_from_c_str)
sea_add_unsat_test(byte_cursor_from_c_str)

# klee
sea_add_klee(byte_cursor_from_c_str
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  aws_byte_cursor_from_c_str_harness.c)

sea_add_fuzz(byte_cursor_from_c_str
  aws_byte_cursor_from_c_str_harness.c)
