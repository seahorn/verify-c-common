add_executable(priority_queue_init_static
  ${AWS_C_COMMON_ROOT}/source/array_list.c
  ${AWS_C_COMMON_ROOT}/source/priority_queue.c
  aws_priority_queue_init_static_harness.c)
target_compile_definitions(priority_queue_init_static
  PUBLIC MAX_ITEM_SIZE=2
  MAX_INITIAL_ITEM_ALLOCATION=9223372036854775808ULL)
sea_attach_bc_link(priority_queue_init_static)
sea_add_unsat_test(priority_queue_init_static)
