add_executable(priority_queue_s_swap
  ${AWS_C_COMMON_ROOT}/source/array_list.c
  aws_priority_queue_s_swap_harness.c)
sea_link_libraries(priority_queue_s_swap priority_queue.opt.ir)
sea_attach_bc_link(priority_queue_s_swap)
configure_file(sea.yaml sea.yaml @ONLY)
sea_add_unsat_test(priority_queue_s_swap)

# klee
if(SEA_ENABLE_KLEE)
  add_executable(
    priority_queue_s_swap.klee
    ${AWS_C_COMMON_ROOT}/source/array_list.c
    aws_priority_queue_s_swap_harness.c
  )
  target_compile_definitions(priority_queue_s_swap.klee PRIVATE __KLEE__)
  sea_link_libraries(priority_queue_s_swap.klee priority_queue.opt.ir)
  klee_attach_bc_link(priority_queue_s_swap.klee)
  sea_add_klee_test(priority_queue_s_swap)
endif()

# smack
if(SEA_ENABLE_SMACK)
  add_executable(
    priority_queue_s_swap.smack
    ${AWS_C_COMMON_ROOT}/source/array_list.c
    aws_priority_queue_s_swap_harness.c
  )
  target_compile_definitions(priority_queue_s_swap.smack PRIVATE __SMACK__)
  sea_link_libraries(priority_queue_s_swap.smack priority_queue.opt.ir)
  smack_attach_bc_link(priority_queue_s_swap.smack)
  sea_add_smack_test(priority_queue_s_swap)
endif()

# symbiotic
if(SEA_ENABLE_SYMBIOTIC)
  add_executable(
    priority_queue_s_swap.symbiotic
    ${AWS_C_COMMON_ROOT}/source/array_list.c
    aws_priority_queue_s_swap_harness.c
  )
  target_compile_definitions(priority_queue_s_swap.symbiotic PRIVATE __SYMBIOTIC__)
  sea_link_libraries(priority_queue_s_swap.symbiotic priority_queue.opt.ir)
  symbiotic_attach_bc_link(priority_queue_s_swap.symbiotic)
  sea_add_symbiotic_test(priority_queue_s_swap)
endif()