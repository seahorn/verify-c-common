add_executable(array_list_swap
  ${AWS_C_COMMON_ROOT}/source/array_list.c
  aws_array_list_swap_harness.c
  ${SEA_LIB}/proof_allocators.c
  ${SEA_LIB}/array_list_helper.c
  ${SEA_LIB}/utils.c
  ${SEA_LIB}/bcmp.c)
target_compile_definitions(array_list_swap
  PUBLIC MAX_ITEM_SIZE=2
  MAX_INITIAL_ITEM_ALLOCATION=9223372036854775808ULL)
sea_attach_bc(array_list_swap)
sea_add_unsat_test(array_list_swap)
