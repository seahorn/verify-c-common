add_executable(byte_buf_secure_zero
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  ${AWS_C_COMMON_ROOT}/source/common.c
  aws_byte_buf_secure_zero_harness.c)
configure_file(sea.yaml sea.yaml @ONLY)
sea_attach_bc_link(byte_buf_secure_zero)
sea_add_unsat_test(byte_buf_secure_zero)

# klee
sea_add_klee(byte_buf_secure_zero ${AWS_C_COMMON_ROOT}/source/byte_buf.c
${AWS_C_COMMON_ROOT}/source/common.c
aws_byte_buf_secure_zero_harness.c)

# fuzz
sea_add_fuzz(byte_buf_secure_zero aws_byte_buf_secure_zero_harness.c)

# smack
sea_add_smack(byte_buf_secure_zero
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  ${AWS_C_COMMON_ROOT}/source/common.c
  aws_byte_buf_secure_zero_harness.c)