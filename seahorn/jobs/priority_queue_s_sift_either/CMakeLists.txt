add_executable(
  priority_queue_s_sift_either
  ${AWS_C_COMMON_ROOT}/source/array_list.c
  aws_priority_queue_s_sift_either_harness.c
)
sea_link_libraries(priority_queue_s_sift_either priority_queue.opt.ir)
sea_attach_bc_link(priority_queue_s_sift_either)
configure_file(sea.yaml sea.yaml @ONLY)
sea_add_unsat_test(priority_queue_s_sift_either)

# klee
if(SEA_ENABLE_KLEE)
  add_executable(
    priority_queue_s_sift_either.klee
    ${AWS_C_COMMON_ROOT}/source/array_list.c
    aws_priority_queue_s_sift_either_harness.c
  )
  target_compile_definitions(priority_queue_s_sift_either.klee PRIVATE __KLEE__)
  sea_link_libraries(priority_queue_s_sift_either.klee priority_queue.opt.ir)
  klee_attach_bc_link(priority_queue_s_sift_either.klee)
  sea_add_klee_test(priority_queue_s_sift_either)
endif()

# smack
if(SEA_ENABLE_SMACK)
  add_executable(
    priority_queue_s_sift_either.smack
    ${AWS_C_COMMON_ROOT}/source/array_list.c
    aws_priority_queue_s_sift_either_harness.c
  )
  target_compile_definitions(priority_queue_s_sift_either.smack PRIVATE __SMACK__)
  sea_link_libraries(priority_queue_s_sift_either.smack priority_queue.opt.ir)
  smack_attach_bc_link(priority_queue_s_sift_either.smack)
  sea_add_smack_test(priority_queue_s_sift_either)
endif()