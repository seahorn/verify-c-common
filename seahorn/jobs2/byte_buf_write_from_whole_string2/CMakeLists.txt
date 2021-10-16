add_executable(byte_buf_write_from_whole_string2
  ${AWS_C_COMMON_ROOT}/source/string.c
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  aws_byte_buf_write_from_whole_string_harness2.c)
sea_attach_bc_link(byte_buf_write_from_whole_string2)
configure_file(sea.yaml sea.yaml @ONLY)
sea_add_unsat_test(byte_buf_write_from_whole_string2)

