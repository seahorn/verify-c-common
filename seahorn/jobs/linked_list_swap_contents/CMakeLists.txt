# add head and tail to list size.
add_executable(linked_list_swap_contents
  aws_linked_list_swap_contents_harness.c
  ${SEA_LIB}/linked_list_helper.c)
sea_attach_bc(linked_list_swap_contents)
sea_add_unsat_test(linked_list_swap_contents)


