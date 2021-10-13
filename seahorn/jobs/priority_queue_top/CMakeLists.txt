add_executable(priority_queue_top
  ${AWS_C_COMMON_ROOT}/source/array_list.c
  ${AWS_C_COMMON_ROOT}/source/priority_queue.c
  aws_priority_queue_top_harness.c)
sea_attach_bc_link(priority_queue_top)
configure_file(sea.yaml sea.yaml @ONLY)
sea_add_unsat_test(priority_queue_top)

