add_executable(array_list_get_at
  ${AWS_C_COMMON_ROOT}/source/array_list.c
  aws_array_list_get_at_harness.c)
sea_attach_bc_link(array_list_get_at)
sea_add_unsat_test(array_list_get_at)

# klee
sea_add_klee(array_list_get_at ${AWS_C_COMMON_ROOT}/source/array_list.c
  aws_array_list_get_at_harness.c)

sea_add_fuzz(array_list_get_at aws_array_list_get_at_harness.c)

# smack
sea_add_smack(array_list_get_at ${AWS_C_COMMON_ROOT}/source/array_list.c
  aws_array_list_get_at_harness.c)