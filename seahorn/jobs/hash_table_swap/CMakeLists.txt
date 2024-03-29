add_executable(hash_table_swap
  aws_hash_table_swap_harness.c)
sea_link_libraries(hash_table_swap hash_table.opt.ir)
sea_overlink_libraries(hash_table_swap hash_table_state_is_valid_override.ir)
sea_attach_bc_link(hash_table_swap)
sea_add_unsat_test(hash_table_swap)

# klee
sea_add_klee(hash_table_swap
  ${AWS_C_COMMON_ROOT}/source/common.c
  ${AWS_C_COMMON_ROOT}/source/hash_table.c
  aws_hash_table_swap_harness.c)

# fuzz
sea_add_fuzz(hash_table_swap aws_hash_table_swap_harness.c)

# smack
sea_add_smack(hash_table_swap
  ${AWS_C_COMMON_ROOT}/source/common.c
  ${AWS_C_COMMON_ROOT}/source/hash_table.c
  aws_hash_table_swap_harness.c)

# symbiotic
sea_add_symbiotic(hash_table_swap
  ${AWS_C_COMMON_ROOT}/source/common.c
  ${AWS_C_COMMON_ROOT}/source/hash_table.c
  aws_hash_table_swap_harness.c
)