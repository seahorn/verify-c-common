add_executable(array_eq_c_str
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  aws_array_eq_c_str_harness.c
  ${SEA_LIB}/proof_allocators.c
  ${SEA_LIB}/utils.c)
set(MAX_BUFFER_SIZE 10)
target_compile_definitions(array_eq_c_str PUBLIC MAX_BUFFER_SIZE=${MAX_BUFFER_SIZE})
sea_attach_bc(array_eq_c_str)
configure_file(sea.yaml sea.yaml @ONLY)
sea_add_unsat_test(array_eq_c_str)

sea_add_fuzz(array_eq_c_str
  aws_array_eq_c_str_harness.c
  ${SEA_LIB}/proof_allocators.c
  ${SEA_LIB}/utils.c)

