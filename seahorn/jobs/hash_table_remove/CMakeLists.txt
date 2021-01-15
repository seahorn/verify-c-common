add_executable(hash_table_remove
  ${AWS_C_COMMON_ROOT}/source/common.c
  aws_hash_table_remove_harness.c)
sea_link_libraries(hash_table_remove hash_table.opt.ir)
sea_overlink_libraries(hash_table_remove safe_eq_check_override.ir)
sea_overlink_libraries(hash_table_remove hash_for_override.ir)
sea_overlink_libraries(hash_table_remove hash_table_state_is_valid_override.ir)
sea_attach_bc_link(hash_table_remove)
configure_file(sea.yaml sea.yaml @ONLY)
sea_add_unsat_test(hash_table_remove)