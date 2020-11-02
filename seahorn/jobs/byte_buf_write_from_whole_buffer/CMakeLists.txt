add_executable(byte_buf_write_from_whole_buffer
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  aws_byte_buf_write_from_whole_buffer_harness.c
  ${SEA_LIB}/proof_allocators.c
  ${SEA_LIB}/byte_buf_helper.c
  ${SEA_LIB}/utils.c)
sea_attach_bc(byte_buf_write_from_whole_buffer)
configure_file(sea.yaml sea.yaml @ONLY)
sea_add_unsat_test(byte_buf_write_from_whole_buffer)
