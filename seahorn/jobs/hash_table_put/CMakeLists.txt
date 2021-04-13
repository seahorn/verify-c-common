add_executable(hash_table_put
  ${AWS_C_COMMON_ROOT}/source/common.c
  aws_hash_table_put_harness.c)
set(MAX_TABLE_SIZE 4)
MATH(EXPR UNROLL_BOUND "2 * ${MAX_TABLE_SIZE}")
target_compile_definitions(hash_table_put
                            PUBLIC
                            MAX_TABLE_SIZE=${MAX_TABLE_SIZE})
sea_link_libraries(hash_table_put hash_table.opt.ir)
sea_overlink_libraries(hash_table_put update_template_size_override.ir)
sea_overlink_libraries(hash_table_put safe_eq_check_override.ir)
sea_overlink_libraries(hash_table_put hash_for_override.ir)
sea_overlink_libraries(hash_table_put emplace_item_override.ir)
sea_overlink_libraries(hash_table_put expand_table_override.ir)
sea_overlink_libraries(hash_table_put hash_table_state_is_valid_override.ir)
sea_attach_bc_link(hash_table_put)
configure_file(sea.yaml sea.yaml @ONLY)
sea_add_unsat_test(hash_table_put)

sea_add_fuzz(hash_table_put aws_hash_table_put_harness.c)
