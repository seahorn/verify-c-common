add_executable(byte_buf_reset
  ${AWS_C_COMMON_ROOT}/source/common.c
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  aws_byte_buf_reset_harness.c)
sea_attach_bc_link(byte_buf_reset)
configure_file(sea.yaml sea.yaml @ONLY)
sea_add_unsat_test(byte_buf_reset)

# klee
sea_add_klee(byte_buf_reset 
  ${AWS_C_COMMON_ROOT}/source/common.c
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  aws_byte_buf_reset_harness.c)

sea_add_fuzz(byte_buf_reset aws_byte_buf_reset_harness.c)
