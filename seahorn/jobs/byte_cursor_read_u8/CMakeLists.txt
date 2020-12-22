add_executable(byte_cursor_read_u8
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  aws_byte_cursor_read_u8_harness.c)
sea_overlink_libraries(byte_cursor_read_u8 byte_cursor_advance_nospec_override.ir)
sea_attach_bc_link(byte_cursor_read_u8)
configure_file(sea.yaml sea.yaml @ONLY)
sea_add_unsat_test(byte_cursor_read_u8)
