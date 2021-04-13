add_executable(hash_table_get_entry_count
  ${AWS_C_COMMON_ROOT}/source/common.c
  aws_hash_table_get_entry_count_harness.c)
sea_link_libraries(hash_table_get_entry_count hash_table.opt.ir)
sea_overlink_libraries(hash_table_get_entry_count hash_table_state_is_valid_override.ir)
sea_attach_bc_link(hash_table_get_entry_count)
sea_add_unsat_test(hash_table_get_entry_count)

# klee
sea_add_klee(hash_table_get_entry_count
  ${AWS_C_COMMON_ROOT}/source/common.c
  ${AWS_C_COMMON_ROOT}/source/hash_table.c
  aws_hash_table_get_entry_count_harness.c)

sea_add_fuzz(hash_table_get_entry_count aws_hash_table_get_entry_count_harness.c)
