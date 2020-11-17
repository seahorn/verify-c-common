add_executable(array_list_push_back
  ${AWS_C_COMMON_ROOT}/source/array_list.c
  aws_array_list_push_back_harness.c)
target_compile_definitions(array_list_push_back
  PUBLIC MAX_ITEM_SIZE=2
  MAX_INITIAL_ITEM_ALLOCATION=9223372036854775808ULL)
sea_attach_bc_link(array_list_push_back)
configure_file(sea.yaml sea.yaml @ONLY)
sea_add_unsat_test(array_list_push_back)

# klee
add_executable(array_list_push_back.klee ${AWS_C_COMMON_ROOT}/source/array_list.c
aws_array_list_push_back_harness.c)
target_compile_definitions(array_list_push_back.klee
  PUBLIC MAX_ITEM_SIZE=2
  MAX_INITIAL_ITEM_ALLOCATION=9223372036854775808ULL)
klee_attach_bc_link(array_list_push_back.klee)