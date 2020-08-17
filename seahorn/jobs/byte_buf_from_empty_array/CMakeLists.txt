add_executable(byte_buf_from_empty_array
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  aws_byte_buf_from_empty_array_harness.c
  ${SEA_LIB}/proof_allocators.c
  ${SEA_LIB}/byte_buf_helper.c
  ${SEA_LIB}/bcmp.c
  ${SEA_LIB}/utils.c)
target_compile_definitions(byte_buf_from_empty_array PUBLIC MAX_BUFFER_SIZE=10 __SEA_AWS_ALLOCATOR__)
sea_attach_bc(byte_buf_from_empty_array)
sea_add_unsat_test(byte_buf_from_empty_array)

