add_executable(byte_buf_from_array
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  aws_byte_buf_from_array_harness.c)
sea_attach_bc_link(byte_buf_from_array)
sea_add_unsat_test(byte_buf_from_array)

# klee
sea_add_klee(byte_buf_from_array ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  aws_byte_buf_from_array_harness.c)

sea_add_fuzz(byte_buf_from_array aws_byte_buf_from_array_harness.c)

# smack
sea_add_smack(byte_buf_from_array ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  aws_byte_buf_from_array_harness.c)

# symbiotic
sea_add_symbiotic(byte_buf_from_array ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  aws_byte_buf_from_array_harness.c)