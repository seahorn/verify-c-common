add_executable(array_list_pop_front
  ${AWS_C_COMMON_ROOT}/source/array_list.c
  aws_array_list_pop_front_harness.c)
sea_attach_bc_link(array_list_pop_front)
configure_file(sea.yaml sea.yaml @ONLY)
sea_add_unsat_test(array_list_pop_front)

# klee
sea_add_klee(array_list_pop_front ${AWS_C_COMMON_ROOT}/source/array_list.c
  aws_array_list_pop_front_harness.c)

sea_add_fuzz(array_list_pop_front aws_array_list_pop_front_harness.c)
