add_executable(byte_buf_reserve_relative
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  aws_byte_buf_reserve_relative_harness.c)
target_compile_definitions(byte_buf_reserve_relative 
  PUBLIC MAX_BUFFER_SIZE=${MAX_BUFFER_SIZE})
sea_attach_bc_link(byte_buf_reserve_relative)
sea_add_unsat_test(byte_buf_reserve_relative)

# klee
sea_add_klee(byte_buf_reserve_relative ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  aws_byte_buf_reserve_relative_harness.c)
