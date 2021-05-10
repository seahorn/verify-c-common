add_executable(byte_cursor_read
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  aws_byte_cursor_read_harness.c)
sea_overlink_libraries(byte_cursor_read byte_cursor_advance_nospec_override.ir)
sea_attach_bc_link(byte_cursor_read)
configure_file(sea.yaml sea.yaml @ONLY)
sea_add_unsat_test(byte_cursor_read)

# fuzz
sea_add_fuzz(byte_cursor_read aws_byte_cursor_read_harness.c)
