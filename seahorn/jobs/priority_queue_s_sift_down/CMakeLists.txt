add_executable(
  priority_queue_s_sift_down
  ${AWS_C_COMMON_ROOT}/source/array_list.c
  aws_priority_queue_s_sift_down_harness.c
)
sea_link_libraries(priority_queue_s_sift_down priority_queue.opt.ir)
sea_attach_bc_link(priority_queue_s_sift_down)
configure_file(sea.yaml sea.yaml @ONLY)
sea_add_unsat_test(priority_queue_s_sift_down)

# klee
if(SEA_ENABLE_KLEE)
  add_executable(
    priority_queue_s_sift_down.klee
    ${AWS_C_COMMON_ROOT}/source/array_list.c
    aws_priority_queue_s_sift_down_harness.c
  )
  target_compile_definitions(priority_queue_s_sift_down.klee PRIVATE __KLEE__)
  sea_link_libraries(priority_queue_s_sift_down.klee priority_queue.opt.ir)
  klee_attach_bc_link(priority_queue_s_sift_down.klee)
  sea_add_klee_test(priority_queue_s_sift_down)
endif()