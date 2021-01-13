add_executable(hash_table_foreach
  ${AWS_C_COMMON_ROOT}/source/common.c
  aws_hash_table_foreach_harness.c)
set(MAX_TABLE_SIZE 2)
MATH(EXPR UNROLL_BOUND "${MAX_TABLE_SIZE} * ${MAX_TABLE_SIZE}")
target_compile_definitions(hash_table_foreach
                            PUBLIC
                            MAX_TABLE_SIZE=${MAX_TABLE_SIZE})
sea_link_libraries(hash_table_foreach hash_table.opt.ir)
sea_overlink_libraries(hash_table_foreach hash_table_state_is_valid_ignore_entry_count_override.ir)
sea_attach_bc_link(hash_table_foreach)
configure_file(sea.yaml sea.yaml @ONLY)
sea_add_unsat_test(hash_table_foreach)