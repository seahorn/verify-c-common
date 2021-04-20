add_executable(
  priority_queue_push
  ${AWS_C_COMMON_ROOT}/source/array_list.c
  aws_priority_queue_push_harness.c
)
sea_link_libraries(priority_queue_push priority_queue.opt.ir)
sea_overlink_libraries(priority_queue_push sift_up_override.ir)
sea_attach_bc_link(priority_queue_push)
configure_file(sea.yaml sea.yaml @ONLY)
sea_add_unsat_test(priority_queue_push)

# klee
sea_add_klee(
  priority_queue_push
  ${AWS_C_COMMON_ROOT}/source/array_list.c
  ${AWS_C_COMMON_ROOT}/source/priority_queue.c
  aws_priority_queue_push_harness.c
)

sea_add_fuzz(
  priority_queue_push
  aws_priority_queue_push_harness.c
)
