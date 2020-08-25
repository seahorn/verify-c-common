add_executable(array_list_comparator_string
  ${AWS_C_COMMON_ROOT}/source/array_list.c
  ${AWS_C_COMMON_ROOT}/source/string.c
  aws_array_list_comparator_string_harness.c
  ${SEA_LIB}/proof_allocators.c
  ${SEA_LIB}/array_list_helper.c
  ${SEA_LIB}/string_helper.c
  ${SEA_LIB}/utils.c
  ${SEA_LIB}/bcmp.c)
target_compile_definitions(array_list_comparator_string
  PUBLIC MAX_ITEM_SIZE=2
  MAX_INITIAL_ITEM_ALLOCATION=9223372036854775808ULL
  MAX_BUFFER_SIZE=10
  MAX_STRING_LEN=16)
configure_file(sea.yaml sea.yaml @ONLY)
sea_attach_bc(array_list_comparator_string)
sea_add_unsat_test(array_list_comparator_string)
