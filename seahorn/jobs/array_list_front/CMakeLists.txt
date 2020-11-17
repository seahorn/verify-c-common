add_executable(array_list_front
  ${AWS_C_COMMON_ROOT}/source/array_list.c
  aws_array_list_front_harness.c)
target_compile_definitions(array_list_front
  PUBLIC MAX_ITEM_SIZE=2
  MAX_INITIAL_ITEM_ALLOCATION=9223372036854775808ULL)
sea_attach_bc_link(array_list_front)
sea_add_unsat_test(array_list_front)

# klee
add_executable(array_list_front.klee ${AWS_C_COMMON_ROOT}/source/array_list.c
aws_array_list_front_harness.c)
target_compile_definitions(array_list_front.klee
  PUBLIC MAX_ITEM_SIZE=2
  MAX_INITIAL_ITEM_ALLOCATION=9223372036854775808ULL)
klee_attach_bc_link(array_list_front.klee)