add_executable(hash_table_eq
  ${AWS_C_COMMON_ROOT}/source/common.c
  aws_hash_table_eq_harness.c)
set(MAX_TABLE_SIZE 8)
target_compile_definitions(hash_table_eq
                            PUBLIC
                            MAX_TABLE_SIZE=${MAX_TABLE_SIZE})
sea_link_libraries(hash_table_eq hash_table.opt.ir)
sea_overlink_libraries(hash_table_eq hash_table_state_is_valid_override.ir)
sea_attach_bc_link(hash_table_eq)
configure_file(sea.yaml sea.yaml @ONLY)
sea_add_unsat_test(hash_table_eq)

# klee
sea_add_klee(hash_table_eq
  ${AWS_C_COMMON_ROOT}/source/common.c
  ${AWS_C_COMMON_ROOT}/source/hash_table.c
  aws_hash_table_eq_harness.c)

sea_add_fuzz(hash_table_eq aws_hash_table_eq_harness.c)
