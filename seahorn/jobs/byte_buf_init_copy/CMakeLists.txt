add_executable(byte_buf_init_copy
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  aws_byte_buf_init_copy_harness.c)
sea_attach_bc_link(byte_buf_init_copy)
configure_file(sea.yaml sea.yaml @ONLY)
sea_add_unsat_test(byte_buf_init_copy)

# klee
sea_add_klee(byte_buf_init_copy ${AWS_C_COMMON_ROOT}/source/byte_buf.c
aws_byte_buf_init_copy_harness.c)

# fuzz
sea_add_fuzz(byte_buf_init_copy aws_byte_buf_init_copy_harness.c)

# smack
sea_add_smack(byte_buf_init_copy ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  aws_byte_buf_init_copy_harness.c)