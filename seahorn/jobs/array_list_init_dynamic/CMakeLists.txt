add_executable(array_list_init_dynamic
  ${AWS_C_COMMON_ROOT}/source/array_list.c
  aws_array_list_init_dynamic_harness.c
  ${SEA_LIB}/proof_allocators.c
  ${SEA_LIB}/array_list_helper.c
  ${SEA_LIB}/utils.c
  ${SEA_LIB}/bcmp.c)
target_compile_definitions(array_list_init_dynamic
  PUBLIC MAX_ITEM_SIZE=2
  MAX_INITIAL_ITEM_ALLOCATION=9223372036854775808ULL
  MAX_BUFFER_SIZE=10)
sea_attach_bc(array_list_init_dynamic)
sea_add_unsat_test(array_list_init_dynamic)
