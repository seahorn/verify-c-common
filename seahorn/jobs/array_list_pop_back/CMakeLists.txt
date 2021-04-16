add_executable(array_list_pop_back
  ${AWS_C_COMMON_ROOT}/source/array_list.c
  aws_array_list_pop_back_harness.c)
sea_attach_bc_link(array_list_pop_back)
sea_add_unsat_test(array_list_pop_back)

# klee
sea_add_klee(array_list_pop_back ${AWS_C_COMMON_ROOT}/source/array_list.c
  aws_array_list_pop_back_harness.c)

sea_add_fuzz(array_list_pop_back aws_array_list_pop_back_harness.c)

# smack
sea_add_smack(array_list_pop_back ${AWS_C_COMMON_ROOT}/source/array_list.c
  aws_array_list_pop_back_harness.c)