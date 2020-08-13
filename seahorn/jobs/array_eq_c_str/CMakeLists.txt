add_executable(array_eq_c_str
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  aws_array_eq_c_str_harness.c
  ${SEA_LIB}/proof_allocators.c
  ${SEA_LIB}/utils.c)
target_compile_definitions(array_eq_c_str PUBLIC MAX_BUFFER_SIZE=10)
sea_attach_bc(array_eq_c_str)
configure_file(sea.yaml sea.yaml @ONLY)

sea_get_file_name(BC array_eq_c_str.ir)
add_test(NAME array_eq_c_str_test COMMAND bash ${VERIFY_SCRIPT} ${BC} "unsat")
