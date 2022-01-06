add_executable(hash_table_create
  ${AWS_C_COMMON_ROOT}/source/common.c
  aws_hash_table_create_harness.c)
set(MAX_TABLE_SIZE 4)
MATH(EXPR UNROLL_BOUND "2 * ${MAX_TABLE_SIZE}")
target_compile_definitions(hash_table_create
                            PUBLIC
                            MAX_TABLE_SIZE=${MAX_TABLE_SIZE})
sea_link_libraries(hash_table_create hash_table.opt.ir)
sea_overlink_libraries(hash_table_create update_template_size_override.ir)
sea_overlink_libraries(hash_table_create safe_eq_check_override.ir)
sea_overlink_libraries(hash_table_create hash_for_override.ir)
sea_overlink_libraries(hash_table_create emplace_item_override.ir)
sea_overlink_libraries(hash_table_create expand_table_override.ir)
sea_overlink_libraries(hash_table_create hash_table_state_is_valid_override.ir)
sea_attach_bc_link(hash_table_create)
configure_file(sea.yaml sea.yaml @ONLY)
sea_add_unsat_test(hash_table_create)

sea_add_fuzz(hash_table_create aws_hash_table_create_harness.c)

# smack
sea_add_smack(hash_table_create
  ${AWS_C_COMMON_ROOT}/source/common.c
  ${AWS_C_COMMON_ROOT}/source/hash_table.c
  aws_hash_table_create_harness.c)

# symbiotic
sea_add_symbiotic(hash_table_create
  ${AWS_C_COMMON_ROOT}/source/common.c
  ${AWS_C_COMMON_ROOT}/source/hash_table.c
  aws_hash_table_create_harness.c
)