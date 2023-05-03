add_executable(hash_table_init_unbounded
  aws_hash_table_init_unbounded_harness.c)
set(MAX_TABLE_SIZE 8)
target_compile_definitions(hash_table_init_unbounded PUBLIC MAX_TABLE_SIZE=${MAX_TABLE_SIZE})
sea_link_libraries(hash_table_init_unbounded hash_table.opt.ir)
sea_overlink_libraries(hash_table_init_unbounded update_template_size_override.ir)
sea_overlink_libraries(hash_table_init_unbounded hash_table_state_is_valid_override.ir)
sea_attach_bc_link(hash_table_init_unbounded)
configure_file(sea.yaml sea.yaml @ONLY)
sea_add_unsat_test(hash_table_init_unbounded)

# klee
sea_add_klee(hash_table_init_unbounded
  ${AWS_C_COMMON_ROOT}/source/common.c
  ${AWS_C_COMMON_ROOT}/source/hash_table.c
  aws_hash_table_init_unbounded_harness.c)

# smack
if(SEA_ENABLE_SMACK)
  sea_add_smack_bc(
    hash_table_init_unbounded
    ${AWS_C_COMMON_ROOT}/source/common.c
    ${AWS_C_COMMON_ROOT}/source/hash_table.c
    aws_hash_table_init_unbounded_harness.c)
  sea_add_smack_test(hash_table_init_unbounded --float)
endif()

# symbiotic
sea_add_symbiotic(hash_table_init_unbounded
  ${AWS_C_COMMON_ROOT}/source/common.c
  ${AWS_C_COMMON_ROOT}/source/hash_table.c
  aws_hash_table_init_unbounded_harness.c
)
