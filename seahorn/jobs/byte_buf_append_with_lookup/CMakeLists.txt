add_executable(byte_buf_append_with_lookup
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  aws_byte_buf_append_with_lookup_harness.c)
sea_attach_bc_link(byte_buf_append_with_lookup)
configure_file(sea.yaml sea.yaml @ONLY)
sea_add_unsat_test(byte_buf_append_with_lookup)

# klee
sea_add_klee(byte_buf_append_with_lookup ${AWS_C_COMMON_ROOT}/source/byte_buf.c
aws_byte_buf_append_with_lookup_harness.c)

# fuzz
sea_add_fuzz(byte_buf_append_with_lookup
  aws_byte_buf_append_with_lookup_harness.c)

# smack
sea_add_smack(byte_buf_append_with_lookup ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  aws_byte_buf_append_with_lookup_harness.c)

# symbiotic
sea_add_symbiotic(byte_buf_append_with_lookup ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  aws_byte_buf_append_with_lookup_harness.c)