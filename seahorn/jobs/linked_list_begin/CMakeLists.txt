add_executable(linked_list_begin
  aws_linked_list_begin_harness.c
  ${SEA_LIB}/linked_list_helper.c)
sea_attach_bc(linked_list_begin)
sea_add_unsat_test(linked_list_begin)