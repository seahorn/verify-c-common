add_executable(byte_buf_init_copy
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  aws_byte_buf_init_copy_harness.c
  ${SEA_LIB}/proof_allocators.c
  ${SEA_LIB}/byte_buf_helper.c
  ${SEA_LIB}/utils.c)
target_compile_definitions(byte_buf_init_copy PUBLIC MAX_BUFFER_SIZE=10 __SEA_AWS_ALLOCATOR__)
sea_attach_bc(byte_buf_init_copy)
configure_file(sea.yaml sea.yaml @ONLY)

sea_get_file_name(BC byte_buf_init_copy.ir)
add_test(NAME byte_buf_init_copy_test COMMAND bash ${VERIFY_SCRIPT} ${BC} "unsat")

