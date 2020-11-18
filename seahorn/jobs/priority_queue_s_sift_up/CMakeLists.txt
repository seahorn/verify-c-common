add_executable(
  priority_queue_s_sift_up
  ${AWS_C_COMMON_ROOT}/source/array_list.c
  aws_priority_queue_s_sift_up_harness.c
)
target_compile_definitions(
  priority_queue_s_sift_up
  PUBLIC MAX_ITEM_SIZE=2
  MAX_INITIAL_ITEM_ALLOCATION=9223372036854775808ULL
  MAX_PRIORITY_QUEUE_ITEMS=5
  MAX_HEAP_HEIGHT=3
)
sea_link_libraries(priority_queue_s_sift_up priority_queue.opt.ir)
sea_attach_bc_link(priority_queue_s_sift_up)
configure_file(sea.yaml sea.yaml @ONLY)
sea_add_unsat_test(priority_queue_s_sift_up)
