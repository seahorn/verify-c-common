add_executable(array_list_clear
  ${AWS_C_COMMON_ROOT}/source/array_list.c
  aws_array_list_clear_harness.c)
sea_attach_bc_link(array_list_clear)
sea_add_unsat_test(array_list_clear)

# klee
sea_add_klee(array_list_clear ${AWS_C_COMMON_ROOT}/source/array_list.c
  aws_array_list_clear_harness.c)

sea_add_fuzz(array_list_clear aws_array_list_clear_harness.c)

# smack
sea_add_smack(array_list_clear ${AWS_C_COMMON_ROOT}/source/array_list.c
  aws_array_list_clear_harness.c)

# symbiotic
sea_add_symbiotic(array_list_clear ${AWS_C_COMMON_ROOT}/source/array_list.c
  aws_array_list_clear_harness.c)