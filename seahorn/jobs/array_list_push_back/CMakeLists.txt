add_executable(array_list_push_back
  ${AWS_C_COMMON_ROOT}/source/array_list.c
  aws_array_list_push_back_harness.c)
sea_attach_bc_link(array_list_push_back)
configure_file(sea.yaml sea.yaml @ONLY)
sea_add_unsat_test(array_list_push_back)

# klee
sea_add_klee(array_list_push_back ${AWS_C_COMMON_ROOT}/source/array_list.c
  aws_array_list_push_back_harness.c)

sea_add_fuzz(array_list_push_back aws_array_list_push_back_harness.c)

# smack
sea_add_smack(array_list_push_back ${AWS_C_COMMON_ROOT}/source/array_list.c
  aws_array_list_push_back_harness.c)