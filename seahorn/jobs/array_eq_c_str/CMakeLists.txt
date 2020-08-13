add_executable(array_eq_c_str
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  aws_array_eq_c_str_harness.c
  ${SEA_LIB}/proof_allocators.c
  ${SEA_LIB}/utils.c)
target_compile_definitions(array_eq_c_str PUBLIC MAX_BUFFER_SIZE=10)
sea_attach_bc(array_eq_c_str)

