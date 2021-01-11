add_executable(hash_table_clean_up
  ${AWS_C_COMMON_ROOT}/source/common.c
  aws_hash_table_clean_up_harness.c)
set(MAX_TABLE_SIZE 8)
math(EXPR MEMCPY_UNROLL_BND "${MAX_TABLE_SIZE} * 32")
target_compile_definitions(hash_table_clean_up PUBLIC MAX_TABLE_SIZE=${MAX_TABLE_SIZE})
sea_link_libraries(hash_table_clean_up hash_table.opt.ir)
sea_overlink_libraries(hash_table_clean_up hash_table_state_is_valid_bounded.ir)
sea_attach_bc_link(hash_table_clean_up)
configure_file(sea.yaml sea.yaml @ONLY)
sea_add_unsat_test(hash_table_clean_up)
