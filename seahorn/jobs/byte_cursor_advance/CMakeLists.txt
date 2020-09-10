add_executable(byte_cursor_advance
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  aws_byte_cursor_advance_harness.c
  ${SEA_LIB}/proof_allocators.c
  ${SEA_LIB}/byte_buf_helper.c
  ${SEA_LIB}/bcmp.c
  ${SEA_LIB}/utils.c)
target_compile_definitions(byte_cursor_advance PUBLIC MAX_BUFFER_SIZE=10)
sea_attach_bc(byte_cursor_advance)
sea_add_unsat_test(byte_cursor_advance)

