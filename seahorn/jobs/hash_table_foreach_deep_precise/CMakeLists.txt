add_executable(hash_table_foreach_deep_precise
  ${AWS_C_COMMON_ROOT}/source/common.c
  aws_hash_table_foreach_deep_precise_harness.c)
set(MAX_TABLE_SIZE 2)
MATH(EXPR UNROLL_BOUND "${MAX_TABLE_SIZE} * ${MAX_TABLE_SIZE}")
target_compile_definitions(hash_table_foreach_deep_precise PUBLIC MAX_TABLE_SIZE=${MAX_TABLE_SIZE})
sea_link_libraries(hash_table_foreach_deep_precise hash_table.opt.ir)
sea_overlink_libraries(hash_table_foreach_deep_precise hash_table_state_is_valid_override.ir)
sea_attach_bc_link(hash_table_foreach_deep_precise)
configure_file(sea.yaml sea.yaml @ONLY)
sea_add_unsat_test(hash_table_foreach_deep_precise)

# smack
sea_add_smack(hash_table_foreach_deep_precise
  ${AWS_C_COMMON_ROOT}/source/common.c
  ${AWS_C_COMMON_ROOT}/source/hash_table.c
  aws_hash_table_foreach_deep_precise_harness.c)