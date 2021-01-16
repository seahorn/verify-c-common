add_executable(array_list_init_dynamic
  ${AWS_C_COMMON_ROOT}/source/array_list.c
  aws_array_list_init_dynamic_harness.c)
sea_attach_bc_link(array_list_init_dynamic)
sea_add_unsat_test(array_list_init_dynamic)

# klee
sea_add_klee(array_list_init_dynamic ${AWS_C_COMMON_ROOT}/source/array_list.c
  aws_array_list_init_dynamic_harness.c)
