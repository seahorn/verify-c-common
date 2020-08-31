add_executable(string_compare
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  ${AWS_C_COMMON_ROOT}/source/string.c
  ${AWS_C_COMMON_ROOT}/source/common.c
  aws_string_compare_harness.c
  ${SEA_LIB}/proof_allocators.c
  ${SEA_LIB}/byte_buf_helper.c
  ${SEA_LIB}/string_helper.c
  ${SEA_LIB}/bcmp.c
  ${SEA_LIB}/utils.c)
set(MAX_STRING_LEN 16)
set(MAX_BUFFER_SIZE ${MAX_STRING_LEN})
target_compile_definitions(string_compare 
		PUBLIC 
		MAX_BUFFER_SIZE=${MAX_BUFFER_SIZE} 
		MAX_STRING_LEN=${MAX_STRING_LEN})
sea_attach_bc(string_compare)
sea_add_unsat_test(string_compare)
