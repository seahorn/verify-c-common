# add head and tail to list size.
add_executable(linked_list_push_back
  aws_linked_list_push_back_harness.c)
sea_attach_bc_link(linked_list_push_back)
sea_add_unsat_test(linked_list_push_back)


