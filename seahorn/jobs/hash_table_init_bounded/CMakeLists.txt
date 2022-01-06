add_executable(hash_table_init_bounded
  aws_hash_table_init_bounded_harness.c)
set(MAX_TABLE_SIZE 8)
math(EXPR MEMCPY_UNROLL_BND "${MAX_TABLE_SIZE} * 64")
target_compile_definitions(hash_table_init_bounded PUBLIC MAX_TABLE_SIZE=${MAX_TABLE_SIZE})
sea_link_libraries(hash_table_init_bounded hash_table.opt.ir)
sea_overlink_libraries(hash_table_init_bounded update_template_size_override.ir)
sea_overlink_libraries(hash_table_init_bounded hash_table_state_is_valid_override.ir)
sea_attach_bc_link(hash_table_init_bounded)
configure_file(sea.yaml sea.yaml @ONLY)
sea_add_unsat_test(hash_table_init_bounded)

# klee
sea_add_klee(hash_table_init_bounded
  ${AWS_C_COMMON_ROOT}/source/common.c
  ${AWS_C_COMMON_ROOT}/source/hash_table.c
  aws_hash_table_init_bounded_harness.c)

# fuzz
sea_add_fuzz(hash_table_init_bounded aws_hash_table_init_bounded_harness.c)

# smack
if(SEA_ENABLE_SMACK)
  sea_add_smack_bc(
    hash_table_init_bounded
    ${AWS_C_COMMON_ROOT}/source/common.c
    ${AWS_C_COMMON_ROOT}/source/hash_table.c
    aws_hash_table_init_bounded_harness.c)
  sea_add_smack_test(hash_table_init_bounded --float)
endif()

# symbiotic
sea_add_symbiotic(hash_table_init_bounded
  ${AWS_C_COMMON_ROOT}/source/common.c
  ${AWS_C_COMMON_ROOT}/source/hash_table.c
  aws_hash_table_init_bounded_harness.c
)