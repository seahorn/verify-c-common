add_executable(string_eq_byte_buf
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  ${AWS_C_COMMON_ROOT}/source/string.c
  ${AWS_C_COMMON_ROOT}/source/error.c
  ${AWS_C_COMMON_ROOT}/source/common.c
  aws_string_eq_byte_buf_harness.c
  ${SEA_LIB}/proof_allocators.c
  ${SEA_LIB}/byte_buf_helper.c
  ${SEA_LIB}/string_helper.c
  ${SEA_LIB}/bcmp.c
  ${SEA_LIB}/utils.c)
target_compile_definitions(string_eq_byte_buf PUBLIC MAX_BUFFER_SIZE=10 MAX_STRING_LEN=16)
sea_attach_bc(string_eq_byte_buf)

sea_get_file_name(BC string_eq_byte_buf.ir)
add_test(NAME string_eq_byte_buf_test COMMAND bash ${VERIFY_SCRIPT} ${BC} "unsat")
