# add head and tail to list size.
MATH(EXPR UNROLL_BOUND "${MAX_LINKED_LIST_ITEM_ALLOCATION_SIZE} + 2")
add_executable(linked_list_push_front
  aws_linked_list_push_front_harness.c
  ${SEA_LIB}/linked_list_helper.c)
target_compile_definitions(linked_list_push_front
  # We will use our own function for is_valid check hence AWS_DEEP_CHECK is off
  PUBLIC AWS_DEEP_CHECKS=0
  MAX_BUFFER_SIZE=${MAX_BUFFER_SIZE}
  MAX_LINKED_LIST_ITEM_ALLOCATION=${MAX_LINKED_LIST_ITEM_ALLOCATION_SIZE})
sea_attach_bc(linked_list_push_front)
sea_add_unsat_test(linked_list_push_front)


