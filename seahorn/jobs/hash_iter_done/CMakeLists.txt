add_executable(
  hash_iter_done
  ${AWS_C_COMMON_ROOT}/source/common.c
  aws_hash_iter_done_harness.c
)
target_compile_definitions(hash_iter_done PUBLIC MAX_TABLE_SIZE=SIZE_MAX)
sea_link_libraries(hash_iter_done hash_table.opt.ir)
sea_overlink_libraries(hash_iter_done hash_table_state_is_valid_bounded.ir)
sea_attach_bc_link(hash_iter_done)
sea_add_unsat_test(hash_iter_done)
