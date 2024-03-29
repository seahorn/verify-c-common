add_executable(
  priority_queue_push_ref
  ${AWS_C_COMMON_ROOT}/source/array_list.c
  aws_priority_queue_push_ref_harness.c
)
sea_link_libraries(priority_queue_push_ref priority_queue.opt.ir)
sea_overlink_libraries(priority_queue_push_ref sift_up_override.ir)
sea_attach_bc_link(priority_queue_push_ref)
configure_file(sea.yaml sea.yaml @ONLY)
sea_add_unsat_test(priority_queue_push_ref)

# klee
if(SEA_ENABLE_KLEE)
  add_executable(
    priority_queue_push_ref.klee
    ${AWS_C_COMMON_ROOT}/source/array_list.c
    aws_priority_queue_push_ref_harness.c
  )
  target_compile_definitions(priority_queue_push_ref.klee PRIVATE __KLEE__)
  sea_link_libraries(priority_queue_push_ref.klee priority_queue.opt.ir)
  klee_attach_bc_link(priority_queue_push_ref.klee)
  sea_add_klee_test(priority_queue_push_ref)
endif()

# fuzz
sea_add_fuzz(
  priority_queue_push_ref
  aws_priority_queue_push_ref_harness.c
)

# smack
if(SEA_ENABLE_SMACK)
  add_executable(
    priority_queue_push_ref.smack
    ${AWS_C_COMMON_ROOT}/source/array_list.c
    aws_priority_queue_push_ref_harness.c
  )
  target_compile_definitions(priority_queue_push_ref.smack PRIVATE __SMACK__)
  sea_link_libraries(priority_queue_push_ref.smack priority_queue.opt.ir)
  smack_attach_bc_link(priority_queue_push_ref.smack)
  sea_add_smack_test(priority_queue_push_ref)
endif()

# symbiotic
if(SEA_ENABLE_SYMBIOTIC)
  add_executable(
    priority_queue_push_ref.symbiotic
    ${AWS_C_COMMON_ROOT}/source/array_list.c
    aws_priority_queue_push_ref_harness.c
  )
  target_compile_definitions(priority_queue_push_ref.symbiotic PRIVATE __SYMBIOTIC__)
  sea_link_libraries(priority_queue_push_ref.symbiotic priority_queue.opt.ir)
  symbiotic_attach_bc_link(priority_queue_push_ref.symbiotic)
  sea_add_symbiotic_test(priority_queue_push_ref)
endif()