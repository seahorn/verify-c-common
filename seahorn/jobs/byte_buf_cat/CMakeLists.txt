add_executable(byte_buf_cat
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  aws_byte_buf_cat_harness.c)
sea_attach_bc_link(byte_buf_cat)
sea_add_unsat_test(byte_buf_cat)

# klee
# Klee will get timeout on this test
# sea_add_klee(byte_buf_cat ${AWS_C_COMMON_ROOT}/source/byte_buf.c
#   aws_byte_buf_cat_harness.c)

# fuzz
sea_add_fuzz(byte_buf_cat aws_byte_buf_cat_harness.c)

# smack
sea_add_smack(byte_buf_cat ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  aws_byte_buf_cat_harness.c)

# symbiotic
sea_add_symbiotic(byte_buf_cat ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  aws_byte_buf_cat_harness.c)