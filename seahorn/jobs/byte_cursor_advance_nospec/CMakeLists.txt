add_executable(byte_cursor_advance_nospec
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  aws_byte_cursor_advance_nospec_harness.c)
sea_attach_bc_link(byte_cursor_advance_nospec)
sea_add_unsat_test(byte_cursor_advance_nospec)

