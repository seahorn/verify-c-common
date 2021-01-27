add_executable(array_list_comparator_string
  ${AWS_C_COMMON_ROOT}/source/array_list.c
  ${AWS_C_COMMON_ROOT}/source/string.c
  aws_array_list_comparator_string_harness.c)
configure_file(sea.yaml sea.yaml @ONLY)
sea_attach_bc_link(array_list_comparator_string)
sea_add_unsat_test(array_list_comparator_string)

# klee
sea_add_klee(array_list_comparator_string
  ${AWS_C_COMMON_ROOT}/source/array_list.c
  ${AWS_C_COMMON_ROOT}/source/string.c
  aws_array_list_comparator_string_harness.c)

sea_add_fuzz(array_list_comparator_string
  aws_array_list_comparator_string_harness.c)
