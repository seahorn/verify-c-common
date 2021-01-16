add_executable(array_list_capacity
  ${AWS_C_COMMON_ROOT}/source/array_list.c
  aws_array_list_capacity_harness.c)
sea_attach_bc_link(array_list_capacity)
sea_add_unsat_test(array_list_capacity)

# klee
sea_add_klee(array_list_capacity ${AWS_C_COMMON_ROOT}/source/array_list.c
aws_array_list_capacity_harness.c)
