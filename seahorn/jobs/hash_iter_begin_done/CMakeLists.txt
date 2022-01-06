add_executable(
  hash_iter_begin_done
  ${AWS_C_COMMON_ROOT}/source/common.c
  aws_hash_iter_begin_done_harness.c
)
set(MAX_TABLE_SIZE 32)
target_compile_definitions(hash_iter_begin_done PUBLIC MAX_TABLE_SIZE=${MAX_TABLE_SIZE})
sea_link_libraries(hash_iter_begin_done hash_table.opt.ir)
sea_overlink_libraries(hash_iter_begin_done hash_table_state_is_valid_override.ir)
sea_attach_bc_link(hash_iter_begin_done)
configure_file(sea.yaml sea.yaml @ONLY)
sea_add_unsat_test(hash_iter_begin_done)

# klee
sea_add_klee(hash_iter_begin_done
  ${AWS_C_COMMON_ROOT}/source/common.c
  ${AWS_C_COMMON_ROOT}/source/hash_table.c
  aws_hash_iter_begin_done_harness.c)

# fuzz
sea_add_fuzz(hash_iter_begin_done
  aws_hash_iter_begin_done_harness.c)

# smack
sea_add_smack(hash_iter_begin_done
  ${AWS_C_COMMON_ROOT}/source/common.c
  ${AWS_C_COMMON_ROOT}/source/hash_table.c
  aws_hash_iter_begin_done_harness.c)

# symbiotic
sea_add_symbiotic(hash_iter_begin_done
  ${AWS_C_COMMON_ROOT}/source/common.c
  ${AWS_C_COMMON_ROOT}/source/hash_table.c
  aws_hash_iter_begin_done_harness.c)