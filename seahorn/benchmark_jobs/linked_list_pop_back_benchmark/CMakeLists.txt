# add head and tail to list size.
MATH(EXPR UNROLL_BOUND "${MAX_LINKED_LIST_ITEM_ALLOCATION_SIZE} + 2")
add_executable(linked_list_pop_back_benchmark
  aws_linked_list_pop_back_harness.c)
target_compile_definitions(linked_list_pop_back_benchmark
  # We will use our own function for is_valid check hence AWS_DEEP_CHECK is off
  PUBLIC AWS_DEEP_CHECKS=0)
sea_attach_bc_link(linked_list_pop_back_benchmark)
sea_add_unsat_test(linked_list_pop_back_benchmark)
