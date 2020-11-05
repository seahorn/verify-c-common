add_executable(byte_buf_init
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  aws_byte_buf_init_harness.c)
sea_attach_bc_link(byte_buf_init)
sea_add_unsat_test(byte_buf_init)

