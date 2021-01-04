add_executable(byte_buf_reserve
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  aws_byte_buf_reserve_harness.c)
target_compile_definitions(byte_buf_reserve 
  PUBLIC MAX_BUFFER_SIZE=${MAX_BUFFER_SIZE})
sea_attach_bc_link(byte_buf_reserve)
sea_add_unsat_test(byte_buf_reserve)

# klee
sea_add_klee(byte_buf_reserve ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  aws_byte_buf_reserve_harness.c)
