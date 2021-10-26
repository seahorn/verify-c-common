add_executable(
  hash_iter_begin2
  ${AWS_C_COMMON_ROOT}/source/common.c
  aws_hash_iter_begin_harness2.c
)
set(MAX_TABLE_SIZE 32)
target_compile_definitions(hash_iter_begin2 PUBLIC MAX_TABLE_SIZE=${MAX_TABLE_SIZE})
sea_link_libraries(hash_iter_begin2 hash_table.opt.ir)
sea_overlink_libraries(hash_iter_begin2 hash_table_state_is_valid_override.ir)
sea_attach_bc_link(hash_iter_begin2)
configure_file(sea.yaml sea.yaml @ONLY)
sea_add_unsat_test(hash_iter_begin2)
