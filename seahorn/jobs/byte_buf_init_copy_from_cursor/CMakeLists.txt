add_executable(byte_buf_init_copy_from_cursor
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  aws_byte_buf_init_copy_from_cursor_harness.c
  ${SEA_LIB}/proof_allocators.c
  ${SEA_LIB}/byte_buf_helper.c
  ${SEA_LIB}/utils.c)
target_compile_definitions(byte_buf_init_copy_from_cursor PUBLIC MAX_BUFFER_SIZE=10)
sea_attach_bc(byte_buf_init_copy_from_cursor)
configure_file(sea.yaml sea.yaml @ONLY)

sea_get_file_name(BC byte_buf_init_copy_from_cursor.ir)
add_test(NAME byte_buf_init_copy_from_cursor_test COMMAND bash ${VERIFY_SCRIPT} ${BC} "unsat")
