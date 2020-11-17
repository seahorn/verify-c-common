add_executable(array_list_comparator_string
  ${AWS_C_COMMON_ROOT}/source/array_list.c
  ${AWS_C_COMMON_ROOT}/source/string.c
  aws_array_list_comparator_string_harness.c)
target_compile_definitions(array_list_comparator_string
  PUBLIC MAX_ITEM_SIZE=2
  MAX_INITIAL_ITEM_ALLOCATION=9223372036854775808ULL)
configure_file(sea.yaml sea.yaml @ONLY)
sea_attach_bc_link(array_list_comparator_string)
sea_add_unsat_test(array_list_comparator_string)

# klee
add_executable(array_list_comparator_string.klee
  ${AWS_C_COMMON_ROOT}/source/array_list.c
  ${AWS_C_COMMON_ROOT}/source/string.c
  aws_array_list_comparator_string_harness.c)
target_compile_definitions(array_list_comparator_string.klee
  PUBLIC MAX_ITEM_SIZE=2
  MAX_INITIAL_ITEM_ALLOCATION=9223372036854775808ULL)
klee_attach_bc_link(array_list_comparator_string.klee)