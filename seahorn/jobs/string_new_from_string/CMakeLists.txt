add_executable(string_new_from_string
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  ${AWS_C_COMMON_ROOT}/source/string.c
  ${AWS_C_COMMON_ROOT}/source/common.c
  aws_string_new_from_string_harness.c
  ${SEA_LIB}/proof_allocators.c
  ${SEA_LIB}/byte_buf_helper.c
  ${SEA_LIB}/string_helper.c
  ${SEA_LIB}/bcmp.c
  ${SEA_LIB}/utils.c)
target_compile_definitions(string_new_from_string PUBLIC MAX_BUFFER_SIZE=10 MAX_STRING_LEN=16)
sea_attach_bc(string_new_from_string)
configure_file(sea.yaml sea.yaml @ONLY)
sea_add_unsat_test(string_new_from_string)
