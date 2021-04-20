add_executable(priority_queue_top
  ${AWS_C_COMMON_ROOT}/source/array_list.c
  ${AWS_C_COMMON_ROOT}/source/priority_queue.c
  aws_priority_queue_top_harness.c)
sea_attach_bc_link(priority_queue_top)
sea_add_unsat_test(priority_queue_top)

# klee
sea_add_klee(priority_queue_top
  ${AWS_C_COMMON_ROOT}/source/array_list.c
  ${AWS_C_COMMON_ROOT}/source/priority_queue.c
  aws_priority_queue_top_harness.c)

sea_add_fuzz(priority_queue_top aws_priority_queue_top_harness.c)
