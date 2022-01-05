add_executable(
  priority_queue_pop
  ${AWS_C_COMMON_ROOT}/source/array_list.c
  aws_priority_queue_pop_harness.c
)
sea_link_libraries(priority_queue_pop priority_queue.opt.ir)
sea_overlink_libraries(priority_queue_pop remove_node_override.ir)
sea_attach_bc_link(priority_queue_pop)
sea_add_unsat_test(priority_queue_pop)

# klee
if(SEA_ENABLE_KLEE)
  add_executable(
    priority_queue_pop.klee
    ${AWS_C_COMMON_ROOT}/source/array_list.c
    aws_priority_queue_pop_harness.c
  )
  target_compile_definitions(priority_queue_pop.klee PRIVATE __KLEE__)
  sea_link_libraries(priority_queue_pop.klee priority_queue.opt.ir)
  klee_attach_bc_link(priority_queue_pop.klee)
  sea_add_klee_test(priority_queue_pop)
endif()

# fuzz
sea_add_fuzz(priority_queue_pop aws_priority_queue_pop_harness.c)

# smack
if(SEA_ENABLE_SMACK)
  add_executable(
    priority_queue_pop.smack
    ${AWS_C_COMMON_ROOT}/source/array_list.c
    aws_priority_queue_pop_harness.c
  )
  target_compile_definitions(priority_queue_pop.smack PRIVATE __SMACK__)
  sea_link_libraries(priority_queue_pop.smack priority_queue.opt.ir)
  smack_attach_bc_link(priority_queue_pop.smack)
  sea_add_smack_test(priority_queue_pop)
endif()

# symbiotic
if(SEA_ENABLE_SYMBIOTIC)
  add_executable(
    priority_queue_pop.symbiotic
    ${AWS_C_COMMON_ROOT}/source/array_list.c
    aws_priority_queue_pop_harness.c
  )
  target_compile_definitions(priority_queue_pop.symbiotic PRIVATE __SYMBIOTIC__)
  sea_link_libraries(priority_queue_pop.symbiotic priority_queue.opt.ir)
  symbiotic_attach_bc_link(priority_queue_pop.symbiotic)
  sea_add_symbiotic_test(priority_queue_pop)
endif()