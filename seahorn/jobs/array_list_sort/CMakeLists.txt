add_executable(array_list_sort
  ${AWS_C_COMMON_ROOT}/source/array_list.c
  aws_array_list_sort_harness.c)
sea_attach_bc_link(array_list_sort)
sea_add_unsat_test(array_list_sort)

# klee
sea_add_klee(array_list_sort ${AWS_C_COMMON_ROOT}/source/array_list.c
  aws_array_list_sort_harness.c)

sea_add_fuzz(array_list_sort aws_array_list_sort_harness.c)

# smack
sea_add_smack(array_list_sort ${AWS_C_COMMON_ROOT}/source/array_list.c
  aws_array_list_sort_harness.c)