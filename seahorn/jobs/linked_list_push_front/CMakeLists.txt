add_executable(linked_list_push_front
  aws_linked_list_push_front_harness.c
  ${SEA_LIB}/linked_list_helper.c)
sea_attach_bc(linked_list_push_front)
sea_add_unsat_test(linked_list_push_front)


