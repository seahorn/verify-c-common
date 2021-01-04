add_executable(array_list_swap
  ${AWS_C_COMMON_ROOT}/source/array_list.c
  aws_array_list_swap_harness.c)
target_compile_definitions(array_list_swap
  PUBLIC MAX_ITEM_SIZE=${MAX_ITEM_SIZE}
  MAX_INITIAL_ITEM_ALLOCATION=${MAX_INITIAL_ITEM_ALLOCATION})
configure_file(sea.yaml sea.yaml @ONLY)
sea_attach_bc_link(array_list_swap)
sea_add_unsat_test(array_list_swap)

# klee
sea_add_klee(array_list_swap ${AWS_C_COMMON_ROOT}/source/array_list.c
  aws_array_list_swap_harness.c)
