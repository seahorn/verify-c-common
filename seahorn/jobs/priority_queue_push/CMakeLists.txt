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
if(SEA_ENABLE_KLEE)
  add_executable(
    priority_queue_push.klee
    ${AWS_C_COMMON_ROOT}/source/array_list.c
    aws_priority_queue_push_harness.c
  )
  target_compile_definitions(priority_queue_push.klee PRIVATE __KLEE__)
  sea_link_libraries(priority_queue_push.klee priority_queue.opt.ir)
  klee_attach_bc_link(priority_queue_push.klee)
  sea_add_klee_test(priority_queue_push)
endif()

# fuzz
sea_add_fuzz(
  priority_queue_push
  aws_priority_queue_push_harness.c
)

# smack
if(SEA_ENABLE_SMACK)
  add_executable(
    priority_queue_push.smack
    ${AWS_C_COMMON_ROOT}/source/array_list.c
    aws_priority_queue_push_harness.c
  )
  target_compile_definitions(priority_queue_push.smack PRIVATE __SMACK__)
  sea_link_libraries(priority_queue_push.smack priority_queue.opt.ir)
  smack_attach_bc_link(priority_queue_push.smack)
  sea_add_smack_test(priority_queue_push)
endif()