add_executable(byte_buf_write
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  aws_byte_buf_write_harness.c)
sea_attach_bc_link(byte_buf_write)
configure_file(sea.yaml sea.yaml @ONLY)
sea_add_unsat_test(byte_buf_write)

# klee
sea_add_klee(byte_buf_write ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  aws_byte_buf_write_harness.c)

# smack
sea_add_smack(byte_buf_write ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  aws_byte_buf_write_harness.c)

# symbiotic
sea_add_symbiotic(byte_buf_write ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  aws_byte_buf_write_harness.c)