add_executable(array_list_capacity
  ${AWS_C_COMMON_ROOT}/source/array_list.c
  aws_array_list_capacity_harness.c)
target_compile_definitions(array_list_capacity
  PUBLIC MAX_ITEM_SIZE=2
  MAX_INITIAL_ITEM_ALLOCATION=9223372036854775808ULL)
sea_attach_bc_link(array_list_capacity)
sea_add_unsat_test(array_list_capacity)

# klee
add_executable(array_list_capacity.klee ${AWS_C_COMMON_ROOT}/source/array_list.c
  aws_array_list_capacity_harness.c)
target_compile_definitions(array_list_capacity.klee
  PUBLIC MAX_ITEM_SIZE=2
  MAX_INITIAL_ITEM_ALLOCATION=9223372036854775808ULL)
klee_attach_bc_link(array_list_capacity.klee)