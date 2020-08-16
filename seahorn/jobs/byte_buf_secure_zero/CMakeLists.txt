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
sea_attach_bc(byte_buf_secure_zero)

sea_get_file_name(BC byte_buf_secure_zero.ir)
add_test(NAME byte_buf_secure_zero_test COMMAND bash ${VERIFY_SCRIPT} ${BC} "unsat")


