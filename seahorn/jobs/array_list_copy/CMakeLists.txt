add_executable(array_list_copy
  ${AWS_C_COMMON_ROOT}/source/array_list.c
  aws_array_list_copy_harness.c)
sea_attach_bc_link(array_list_copy)
sea_add_unsat_test(array_list_copy)

# klee
sea_add_klee(array_list_copy ${AWS_C_COMMON_ROOT}/source/array_list.c
  aws_array_list_copy_harness.c)

sea_add_fuzz(array_list_copy aws_array_list_copy_harness.c)