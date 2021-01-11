add_executable(
  priority_queue_remove
  ${AWS_C_COMMON_ROOT}/source/array_list.c
  aws_priority_queue_remove_harness.c
)
target_compile_definitions(
  priority_queue_remove
  PUBLIC MAX_PRIORITY_QUEUE_ITEMS=5
  MAX_HEAP_HEIGHT=3
)
sea_link_libraries(priority_queue_remove priority_queue.opt.ir)
sea_overlink_libraries(priority_queue_remove remove_node_override.ir)
sea_attach_bc_link(priority_queue_remove)
sea_add_unsat_test(priority_queue_remove)

# klee
sea_add_klee(priority_queue_remove
  ${AWS_C_COMMON_ROOT}/source/array_list.c
  ${AWS_C_COMMON_ROOT}/source/priority_queue.c
  aws_priority_queue_remove_harness.c)