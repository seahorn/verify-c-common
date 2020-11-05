# add head and tail to list size.
add_executable(linked_list_rbegin
  aws_linked_list_rbegin_harness.c)
target_compile_definitions(linked_list_rbegin
  # We will use our own function for is_valid check hence AWS_DEEP_CHECK is off
  PUBLIC SEA_DEEP_CHECKS=0)
sea_attach_bc_link(linked_list_rbegin)
sea_add_unsat_test(linked_list_rbegin)
