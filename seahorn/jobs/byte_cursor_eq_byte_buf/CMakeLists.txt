add_executable(byte_cursor_eq_byte_buf
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  aws_byte_cursor_eq_byte_buf_harness.c)
sea_attach_bc_link(byte_cursor_eq_byte_buf)
sea_add_unsat_test(byte_cursor_eq_byte_buf)

# klee
sea_add_klee(byte_cursor_eq_byte_buf
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  aws_byte_cursor_eq_byte_buf_harness.c)
