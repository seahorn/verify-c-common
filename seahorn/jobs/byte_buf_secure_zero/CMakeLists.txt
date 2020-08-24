add_executable(byte_buf_secure_zero
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  ${AWS_C_COMMON_ROOT}/source/common.c
  aws_byte_buf_secure_zero_harness.c
  ${SEA_LIB}/proof_allocators.c
  ${SEA_LIB}/byte_buf_helper.c
  ${SEA_LIB}/bcmp.c
  ${SEA_LIB}/utils.c)
target_compile_definitions(byte_buf_secure_zero PUBLIC
  MAX_BUFFER_SIZE=10)
configure_file(sea.yaml sea.yaml @ONLY)
sea_attach_bc(byte_buf_secure_zero)
sea_add_unsat_test(byte_buf_secure_zero)


