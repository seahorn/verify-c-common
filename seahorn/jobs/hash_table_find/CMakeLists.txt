add_executable(hash_table_find
  ${AWS_C_COMMON_ROOT}/source/common.c
  aws_hash_table_find_harness.c)
set(MAX_TABLE_SIZE 8)
target_compile_definitions(hash_table_find
                            PUBLIC
                            MAX_TABLE_SIZE=${MAX_TABLE_SIZE})
sea_link_libraries(hash_table_find hash_table.opt.ir)
sea_overlink_libraries(hash_table_find safe_eq_check_override.ir)
sea_overlink_libraries(hash_table_find hash_for_override.ir)
sea_overlink_libraries(hash_table_find hash_table_state_is_valid_override.ir)
sea_attach_bc_link(hash_table_find)
configure_file(sea.yaml sea.yaml @ONLY)
sea_add_unsat_test(hash_table_find)

# klee
sea_add_klee(hash_table_find
  ${AWS_C_COMMON_ROOT}/source/common.c
  ${AWS_C_COMMON_ROOT}/source/hash_table.c
  aws_hash_table_find_harness.c)

# fuzz
sea_add_fuzz(hash_table_find aws_hash_table_find_harness.c)

# smack
sea_add_smack(hash_table_find
  ${AWS_C_COMMON_ROOT}/source/common.c
  ${AWS_C_COMMON_ROOT}/source/hash_table.c
  aws_hash_table_find_harness.c)