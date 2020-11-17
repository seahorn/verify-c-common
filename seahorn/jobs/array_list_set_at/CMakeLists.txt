add_executable(array_list_set_at
  ${AWS_C_COMMON_ROOT}/source/array_list.c
  aws_array_list_set_at_harness.c)
target_compile_definitions(array_list_set_at
  PUBLIC MAX_ITEM_SIZE=2
  MAX_INITIAL_ITEM_ALLOCATION=9223372036854775808ULL)
sea_attach_bc_link(array_list_set_at)
configure_file(sea.yaml sea.yaml @ONLY)
sea_add_unsat_test(array_list_set_at)

# klee
add_executable(array_list_set_at.klee ${AWS_C_COMMON_ROOT}/source/array_list.c
  aws_array_list_set_at_harness.c)
target_compile_definitions(array_list_set_at.klee
  PUBLIC MAX_ITEM_SIZE=2
  MAX_INITIAL_ITEM_ALLOCATION=9223372036854775808ULL)
klee_attach_bc_link(array_list_set_at.klee)