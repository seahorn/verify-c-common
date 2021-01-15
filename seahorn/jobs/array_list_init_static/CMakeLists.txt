add_executable(array_list_init_static
  ${AWS_C_COMMON_ROOT}/source/array_list.c
  aws_array_list_init_static_harness.c)
sea_attach_bc_link(array_list_init_static)
sea_add_unsat_test(array_list_init_static)

# klee
sea_add_klee(array_list_init_static ${AWS_C_COMMON_ROOT}/source/array_list.c
  aws_array_list_init_static_harness.c)
