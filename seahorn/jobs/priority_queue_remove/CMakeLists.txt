add_executable(
  priority_queue_remove
  ${AWS_C_COMMON_ROOT}/source/array_list.c
  aws_priority_queue_remove_harness.c
)
sea_link_libraries(priority_queue_remove priority_queue.opt.ir)
sea_overlink_libraries(priority_queue_remove remove_node_override.ir)
sea_attach_bc_link(priority_queue_remove)
sea_add_unsat_test(priority_queue_remove)

# klee
if(SEA_ENABLE_KLEE)
  add_executable(
    priority_queue_remove.klee
    ${AWS_C_COMMON_ROOT}/source/array_list.c
    aws_priority_queue_remove_harness.c
  )
  target_compile_definitions(priority_queue_remove.klee PRIVATE __KLEE__)
  sea_link_libraries(priority_queue_remove.klee priority_queue.opt.ir)
  klee_attach_bc_link(priority_queue_remove.klee)
  sea_add_klee_test(priority_queue_remove)
endif()

# fuzz
sea_add_fuzz(
  priority_queue_remove
  aws_priority_queue_remove_harness.c
)

# smack
if(SEA_ENABLE_SMACK)
  add_executable(
    priority_queue_remove.smack
    ${AWS_C_COMMON_ROOT}/source/array_list.c
    aws_priority_queue_remove_harness.c
  )
  target_compile_definitions(priority_queue_remove.smack PRIVATE __SMACK__)
  sea_link_libraries(priority_queue_remove.smack priority_queue.opt.ir)
  smack_attach_bc_link(priority_queue_remove.smack)
  sea_add_smack_test(priority_queue_remove)
endif()

# symbiotic
if(SEA_ENABLE_SYMBIOTIC)
  add_executable(
    priority_queue_remove.symbiotic
    ${AWS_C_COMMON_ROOT}/source/array_list.c
    aws_priority_queue_remove_harness.c
  )
  target_compile_definitions(priority_queue_remove.symbiotic PRIVATE __SYMBIOTIC__)
  sea_link_libraries(priority_queue_remove.symbiotic priority_queue.opt.ir)
  symbiotic_attach_bc_link(priority_queue_remove.symbiotic)
  sea_add_symbiotic_test(priority_queue_remove)
endif()