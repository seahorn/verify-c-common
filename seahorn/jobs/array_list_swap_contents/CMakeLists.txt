add_executable(array_list_swap_contents
  ${AWS_C_COMMON_ROOT}/source/array_list.c
  aws_array_list_swap_contents_harness.c)
target_compile_definitions(array_list_swap_contents
  PUBLIC MAX_ITEM_SIZE=${MAX_ITEM_SIZE}
  MAX_INITIAL_ITEM_ALLOCATION=${MAX_INITIAL_ITEM_ALLOCATION})
sea_attach_bc_link(array_list_swap_contents)
sea_add_unsat_test(array_list_swap_contents)

# klee
sea_add_klee(array_list_swap_contents ${AWS_C_COMMON_ROOT}/source/array_list.c
  aws_array_list_swap_contents_harness.c)
