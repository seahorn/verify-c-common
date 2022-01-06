add_executable(
  hash_iter_delete
  ${AWS_C_COMMON_ROOT}/source/common.c
  aws_hash_iter_delete_harness.c
)
sea_link_libraries(hash_iter_delete hash_table.opt.ir)
sea_overlink_libraries(hash_iter_delete hash_table_state_is_valid_override.ir)
sea_attach_bc_link(hash_iter_delete)
configure_file(sea.yaml sea.yaml @ONLY)
sea_add_unsat_test(hash_iter_delete)

# fuzz
sea_add_fuzz(hash_iter_delete aws_hash_iter_delete_harness.c)

# smack
sea_add_smack(hash_iter_delete
  ${AWS_C_COMMON_ROOT}/source/common.c
  ${AWS_C_COMMON_ROOT}/source/hash_table.c
  aws_hash_iter_delete_harness.c)

# symbiotic
sea_add_symbiotic(hash_iter_delete
  ${AWS_C_COMMON_ROOT}/source/common.c
  ${AWS_C_COMMON_ROOT}/source/hash_table.c
  aws_hash_iter_delete_harness.c)