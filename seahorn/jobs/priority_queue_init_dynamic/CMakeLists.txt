add_executable(priority_queue_init_dynamic
  ${AWS_C_COMMON_ROOT}/source/array_list.c
  ${AWS_C_COMMON_ROOT}/source/priority_queue.c
  aws_priority_queue_init_dynamic_harness.c)
target_compile_definitions(priority_queue_init_dynamic
  PUBLIC MAX_ITEM_SIZE=2
  MAX_INITIAL_ITEM_ALLOCATION=9223372036854775808ULL)
sea_attach_bc_link(priority_queue_init_dynamic)
sea_add_unsat_test(priority_queue_init_dynamic)
