add_executable(array_list_clear
  ${AWS_C_COMMON_ROOT}/source/array_list.c
  aws_array_list_clear_harness.c
  ${SEA_LIB}/proof_allocators.c
  ${SEA_LIB}/array_list_helper.c
  ${SEA_LIB}/utils.c)
target_compile_definitions(array_list_clear
  PUBLIC MAX_ITEM_SIZE=2
  MAX_INITIAL_ITEM_ALLOCATION=9223372036854775808ULL
  MAX_BUFFER_SIZE=10)
sea_attach_bc(array_list_clear)

sea_get_file_name(BC array_list_clear.ir)
add_test(NAME array_list_clear_test COMMAND bash ${VERIFY_SCRIPT} ${BC} "unsat")
