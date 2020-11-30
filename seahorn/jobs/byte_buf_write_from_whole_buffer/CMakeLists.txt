add_executable(byte_buf_write_from_whole_buffer
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  aws_byte_buf_write_from_whole_buffer_harness.c)
sea_attach_bc_link(byte_buf_write_from_whole_buffer)
configure_file(sea.yaml sea.yaml @ONLY)
sea_add_unsat_test(byte_buf_write_from_whole_buffer)

# klee
sea_add_klee(byte_buf_write_from_whole_buffer ${AWS_C_COMMON_ROOT}/source/byte_buf.c
aws_byte_buf_write_from_whole_buffer_harness.c)