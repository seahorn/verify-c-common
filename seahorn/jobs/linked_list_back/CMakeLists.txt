add_executable(linked_list_back
  aws_linked_list_back_harness.c
  ${SEA_LIB}/linked_list_helper.c)
sea_attach_bc(linked_list_back)
sea_add_unsat_test(linked_list_back)


