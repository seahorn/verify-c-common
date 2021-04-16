add_executable(array_list_set_at
  ${AWS_C_COMMON_ROOT}/source/array_list.c
  aws_array_list_set_at_harness.c)
sea_attach_bc_link(array_list_set_at)
configure_file(sea.yaml sea.yaml @ONLY)
sea_add_unsat_test(array_list_set_at)

# klee
sea_add_klee(array_list_set_at ${AWS_C_COMMON_ROOT}/source/array_list.c
  aws_array_list_set_at_harness.c)

sea_add_fuzz(array_list_set_at aws_array_list_set_at_harness.c)

# smack
sea_add_smack(array_list_set_at ${AWS_C_COMMON_ROOT}/source/array_list.c
  aws_array_list_set_at_harness.c)