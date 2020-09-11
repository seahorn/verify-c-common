add_executable(byte_cursor_compare_lookup
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  aws_byte_cursor_compare_lookup_harness.c
  ${SEA_LIB}/proof_allocators.c
  ${SEA_LIB}/byte_buf_helper.c
  ${SEA_LIB}/bcmp.c
  ${SEA_LIB}/utils.c)
set(MAX_BUFFER_SIZE 10)
target_compile_definitions(byte_cursor_compare_lookup PUBLIC MAX_BUFFER_SIZE=${MAX_BUFFER_SIZE})
sea_attach_bc(byte_cursor_compare_lookup)
configure_file(sea.yaml sea.yaml @ONLY)
sea_add_unsat_test(byte_cursor_compare_lookup)

