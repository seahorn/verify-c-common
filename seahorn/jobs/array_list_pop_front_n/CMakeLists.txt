add_executable(array_list_pop_front_n
  ${AWS_C_COMMON_ROOT}/source/array_list.c
  aws_array_list_pop_front_n_harness.c)
sea_attach_bc_link(array_list_pop_front_n)
configure_file(sea.yaml sea.yaml @ONLY)
sea_add_unsat_test(array_list_pop_front_n)

# klee
sea_add_klee(array_list_pop_front_n ${AWS_C_COMMON_ROOT}/source/array_list.c
  aws_array_list_pop_front_n_harness.c)

sea_add_fuzz(array_list_pop_front_n aws_array_list_pop_front_n_harness.c)

# smack
sea_add_smack(array_list_pop_front_n ${AWS_C_COMMON_ROOT}/source/array_list.c
  aws_array_list_pop_front_n_harness.c)

# symbiotic
sea_add_symbiotic(array_list_pop_front_n ${AWS_C_COMMON_ROOT}/source/array_list.c
  aws_array_list_pop_front_n_harness.c)