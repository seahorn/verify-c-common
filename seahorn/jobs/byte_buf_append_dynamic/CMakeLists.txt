add_executable(byte_buf_append_dynamic
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  aws_byte_buf_append_dynamic_harness.c)
target_compile_definitions(byte_buf_append_dynamic PUBLIC __SEA_AWS_ALLOCATOR__)
sea_attach_bc_link(byte_buf_append_dynamic)
sea_add_unsat_test(byte_buf_append_dynamic)

# klee
sea_add_klee(byte_buf_append_dynamic ${AWS_C_COMMON_ROOT}/source/byte_buf.c
aws_byte_buf_append_dynamic_harness.c)

# fuzz
sea_add_fuzz(byte_buf_append_dynamic aws_byte_buf_append_dynamic_harness.c)

# smack
sea_add_smack(byte_buf_append_dynamic ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  aws_byte_buf_append_dynamic_harness.c)

# symbiotic
sea_add_symbiotic(byte_buf_append_dynamic ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  aws_byte_buf_append_dynamic_harness.c)