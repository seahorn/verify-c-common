add_executable(array_list_shrink_to_fit
  ${AWS_C_COMMON_ROOT}/source/array_list.c
  aws_array_list_shrink_to_fit_harness.c)
sea_attach_bc_link(array_list_shrink_to_fit)
sea_add_unsat_test(array_list_shrink_to_fit)

# klee
sea_add_klee(array_list_shrink_to_fit ${AWS_C_COMMON_ROOT}/source/array_list.c
  aws_array_list_shrink_to_fit_harness.c)

sea_add_fuzz(array_list_shrink_to_fit aws_array_list_shrink_to_fit_harness.c)

# smack
sea_add_smack(array_list_shrink_to_fit ${AWS_C_COMMON_ROOT}/source/array_list.c
  aws_array_list_shrink_to_fit_harness.c)