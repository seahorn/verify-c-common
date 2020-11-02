add_executable(byte_buf_append_with_lookup
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  aws_byte_buf_append_with_lookup_harness.c
  ${SEA_LIB}/proof_allocators.c
  ${SEA_LIB}/byte_buf_helper.c
  ${SEA_LIB}/utils.c)
sea_attach_bc(byte_buf_append_with_lookup)
configure_file(sea.yaml sea.yaml @ONLY)
sea_add_unsat_test(byte_buf_append_with_lookup)
