add_executable(byte_buf_write_u8
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  aws_byte_buf_write_u8_harness.c
  ${SEA_LIB}/proof_allocators.c
  ${SEA_LIB}/byte_buf_helper.c
  ${SEA_LIB}/utils.c)
target_compile_definitions(byte_buf_write_u8 PUBLIC MAX_BUFFER_SIZE=10)
sea_attach_bc(byte_buf_write_u8)

sea_get_file_name(BC byte_buf_write_u8.ir)
add_test(NAME byte_buf_write_u8_test COMMAND bash ${VERIFY_SCRIPT} ${BC} "unsat")

