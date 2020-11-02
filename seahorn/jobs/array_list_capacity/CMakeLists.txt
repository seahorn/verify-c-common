add_executable(array_list_capacity
  ${AWS_C_COMMON_ROOT}/source/array_list.c
  aws_array_list_capacity_harness.c
  ${SEA_LIB}/proof_allocators.c
  ${SEA_LIB}/array_list_helper.c
  ${SEA_LIB}/utils.c)
target_compile_definitions(array_list_capacity
  PUBLIC MAX_ITEM_SIZE=2
  MAX_INITIAL_ITEM_ALLOCATION=9223372036854775808ULL)
sea_attach_bc(array_list_capacity)
sea_add_unsat_test(array_list_capacity)
