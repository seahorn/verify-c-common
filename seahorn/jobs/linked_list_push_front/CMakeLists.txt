# add head and tail to list size.
add_executable(linked_list_push_front
  aws_linked_list_push_front_harness.c)
sea_attach_bc(linked_list_push_front)
sea_add_unsat_test(linked_list_push_front)


