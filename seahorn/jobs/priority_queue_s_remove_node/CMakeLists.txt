add_executable(
  priority_queue_s_remove_node
  ${AWS_C_COMMON_ROOT}/source/array_list.c
  aws_priority_queue_s_remove_node_harness.c
)
sea_link_libraries(priority_queue_s_remove_node priority_queue.opt.ir)
sea_overlink_libraries(priority_queue_s_remove_node sift_either_override.ir)
sea_attach_bc_link(priority_queue_s_remove_node)
configure_file(sea.yaml sea.yaml @ONLY)
sea_add_unsat_test(priority_queue_s_remove_node)

# klee
sea_add_klee(priority_queue_s_remove_node
  ${AWS_C_COMMON_ROOT}/source/array_list.c
  ${AWS_C_COMMON_ROOT}/source/priority_queue.c
  aws_priority_queue_s_remove_node_harness.c)

# smack
if(SEA_ENABLE_SMACK)
  add_executable(
    priority_queue_s_remove_node.smack
    ${AWS_C_COMMON_ROOT}/source/array_list.c
    aws_priority_queue_s_remove_node_harness.c
  )
  target_compile_definitions(priority_queue_s_remove_node.smack PRIVATE __SMACK__)
  sea_link_libraries(priority_queue_s_remove_node.smack priority_queue.opt.ir)
  smack_attach_bc_link(priority_queue_s_remove_node.smack)
  sea_add_smack_test(priority_queue_s_remove_node)
endif()

# symbiotic
if(SEA_ENABLE_SYMBIOTIC)
  add_executable(
    priority_queue_s_remove_node.symbiotic
    ${AWS_C_COMMON_ROOT}/source/array_list.c
    aws_priority_queue_s_remove_node_harness.c
  )
  target_compile_definitions(priority_queue_s_remove_node.symbiotic PRIVATE __SYMBIOTIC__)
  sea_link_libraries(priority_queue_s_remove_node.symbiotic priority_queue.opt.ir)
  symbiotic_attach_bc_link(priority_queue_s_remove_node.symbiotic)
  sea_add_symbiotic_test(priority_queue_s_remove_node)
endif()