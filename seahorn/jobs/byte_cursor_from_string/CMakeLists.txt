add_executable(byte_cursor_from_string
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  ${AWS_C_COMMON_ROOT}/source/string.c
  aws_byte_cursor_from_string_harness.c
  ${SEA_LIB}/proof_allocators.c
  ${SEA_LIB}/byte_buf_helper.c
  ${SEA_LIB}/string_helper.c
  ${SEA_LIB}/bcmp.c
  ${SEA_LIB}/utils.c)
sea_attach_bc(byte_cursor_from_string)
configure_file(sea.yaml sea.yaml @ONLY)
sea_add_unsat_test(byte_cursor_from_string)

