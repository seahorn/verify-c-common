add_executable(byte_buf_eq_c_str_ignore_case
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  aws_byte_buf_eq_c_str_ignore_case_harness.c
  ${SEA_LIB}/proof_allocators.c
  ${SEA_LIB}/byte_buf_helper.c
  ${SEA_LIB}/bcmp.c
  ${SEA_LIB}/utils.c)
set(MAX_BUFFER_SIZE 10)
target_compile_definitions(byte_buf_eq_c_str_ignore_case 
		PUBLIC MAX_BUFFER_SIZE=${MAX_BUFFER_SIZE} __SEA_AWS_ALLOCATOR__)
configure_file(sea.yaml sea.yaml @ONLY)
sea_attach_bc(byte_buf_eq_c_str_ignore_case)
sea_add_unsat_test(byte_buf_eq_c_str_ignore_case)

