add_executable(byte_cursor_eq_byte_buf
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  aws_byte_cursor_eq_byte_buf_harness.c
  ${SEA_LIB}/proof_allocators.c
  ${SEA_LIB}/byte_buf_helper.c
  ${SEA_LIB}/bcmp.c
  ${SEA_LIB}/utils.c)
target_compile_definitions(byte_cursor_eq_byte_buf PUBLIC MAX_BUFFER_SIZE=10)
sea_attach_bc(byte_cursor_eq_byte_buf)

sea_get_file_name(BC byte_cursor_eq_byte_buf.ir)
add_test(NAME byte_cursor_eq_byte_buf_test COMMAND bash ${VERIFY_SCRIPT} ${BC} "unsat")

