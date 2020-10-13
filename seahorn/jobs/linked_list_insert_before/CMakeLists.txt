add_executable(linked_list_insert_before
  aws_linked_list_insert_before_harness.c
  ${SEA_LIB}/linked_list_helper.c)
sea_attach_bc(linked_list_insert_before)
sea_add_unsat_test(linked_list_insert_before)
