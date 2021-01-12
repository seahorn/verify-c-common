add_executable(byte_cursor_from_array
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  aws_byte_cursor_from_array_harness.c)
sea_attach_bc_link(byte_cursor_from_array)
sea_add_unsat_test(byte_cursor_from_array)

# klee
sea_add_klee(byte_cursor_from_array
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  aws_byte_cursor_from_array_harness.c)
