add_executable(byte_buf_eq_cex
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  aws_byte_buf_eq_cex_harness.c
  ${SEA_LIB}/proof_allocators.c
  ${SEA_LIB}/byte_buf_helper.c
  ${SEA_LIB}/bcmp.c
  ${SEA_LIB}/cex_utils.c)
set(MAX_BUFFER_SIZE 10)
target_compile_definitions(byte_buf_eq_cex PUBLIC MAX_BUFFER_SIZE=${MAX_BUFFER_SIZE} __SEA_AWS_ALLOCATOR__)
sea_attach_bc(byte_buf_eq_cex)
configure_file(sea.yaml sea.yaml @ONLY)
# sea_add_unsat_test(byte_buf_eq_cex)

