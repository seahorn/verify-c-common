add_executable(byte_buf_write_from_whole_string
  ${AWS_C_COMMON_ROOT}/source/string.c
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  aws_byte_buf_write_from_whole_string_harness.c
  ${SEA_LIB}/proof_allocators.c
  ${SEA_LIB}/byte_buf_helper.c
  ${SEA_LIB}/string_helper.c
  ${SEA_LIB}/utils.c)
target_compile_definitions(byte_buf_write_from_whole_string PUBLIC MAX_BUFFER_SIZE=10 MAX_STRING_LEN=16)
sea_attach_bc(byte_buf_write_from_whole_string)
configure_file(sea.yaml sea.yaml @ONLY)
sea_add_unsat_test(byte_buf_write_from_whole_string)

