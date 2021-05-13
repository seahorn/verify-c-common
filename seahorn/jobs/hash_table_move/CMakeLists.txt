add_executable(hash_table_move
  aws_hash_table_move_harness.c)
sea_link_libraries(hash_table_move hash_table.opt.ir)
sea_overlink_libraries(hash_table_move hash_table_state_is_valid_override.ir)
sea_attach_bc_link(hash_table_move)
sea_add_unsat_test(hash_table_move)

# klee
sea_add_klee(hash_table_move
  ${AWS_C_COMMON_ROOT}/source/common.c
  ${AWS_C_COMMON_ROOT}/source/hash_table.c
  aws_hash_table_move_harness.c)

# fuzz
sea_add_fuzz(hash_table_move aws_hash_table_move_harness.c)

# smack
sea_add_smack(hash_table_move
  ${AWS_C_COMMON_ROOT}/source/common.c
  ${AWS_C_COMMON_ROOT}/source/hash_table.c
  aws_hash_table_move_harness.c)