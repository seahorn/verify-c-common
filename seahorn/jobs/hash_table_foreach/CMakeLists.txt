add_executable(hash_table_foreach
  ${AWS_C_COMMON_ROOT}/source/common.c
  aws_hash_table_foreach_harness.c)
sea_link_libraries(hash_table_foreach hash_table.opt.ir)
sea_overlink_libraries(hash_table_foreach hash_table_state_is_valid_bounded.ir)
sea_attach_bc_link(hash_table_foreach)
configure_file(sea.yaml sea.yaml @ONLY)
sea_add_unsat_test(hash_table_foreach)