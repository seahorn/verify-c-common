add_executable(array_list_push_back2
  ${AWS_C_COMMON_ROOT}/source/array_list.c
  aws_array_list_push_back_harness2.c)
sea_attach_bc_link(array_list_push_back2)
configure_file(sea.yaml sea.yaml @ONLY)
sea_add_unsat_test(array_list_push_back2)

