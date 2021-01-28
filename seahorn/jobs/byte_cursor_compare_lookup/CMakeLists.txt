add_executable(byte_cursor_compare_lookup
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  aws_byte_cursor_compare_lookup_harness.c)
sea_attach_bc_link(byte_cursor_compare_lookup)
configure_file(sea.yaml sea.yaml @ONLY)
sea_add_unsat_test(byte_cursor_compare_lookup)

# klee
sea_add_klee(byte_cursor_compare_lookup
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  aws_byte_cursor_compare_lookup_harness.c)

sea_add_fuzz(byte_cursor_compare_lookup
  aws_byte_cursor_compare_lookup_harness.c)
