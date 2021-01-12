add_executable(byte_buf_from_empty_array
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  aws_byte_buf_from_empty_array_harness.c)
sea_attach_bc_link(byte_buf_from_empty_array)
sea_add_unsat_test(byte_buf_from_empty_array)

# klee
sea_add_klee(byte_buf_from_empty_array ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  aws_byte_buf_from_empty_array_harness.c)
