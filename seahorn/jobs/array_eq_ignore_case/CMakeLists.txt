add_executable(array_eq_ignore_case
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  aws_array_eq_ignore_case_harness.c
  ${SEA_LIB}/proof_allocators.c
  ${SEA_LIB}/utils.c)
target_compile_definitions(array_eq_ignore_case PUBLIC MAX_BUFFER_SIZE=10)
sea_attach_bc(array_eq_ignore_case)

sea_get_file_name(BC array_eq_ignore_case.ir)
add_test(NAME array_eq_ignore_case_test COMMAND bash ${VERIFY_SCRIPT} ${BC} "unsat")
