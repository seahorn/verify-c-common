add_executable(byte_buf_eq
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  aws_byte_buf_eq_harness.c)
sea_attach_bc_link(byte_buf_eq)
configure_file(sea.yaml sea.yaml @ONLY)
sea_add_unsat_test(byte_buf_eq)

# klee
sea_add_klee(byte_buf_eq ${AWS_C_COMMON_ROOT}/source/byte_buf.c
aws_byte_buf_eq_harness.c)

# fuzz
sea_add_fuzz(byte_buf_eq
  aws_byte_buf_eq_harness.c)

# smack
if(SEA_ENABLE_SMACK)
  sea_add_smack_bc(byte_buf_eq ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  aws_byte_buf_eq_harness.c)
  sea_add_smack_test(byte_buf_eq --strings)
endif()

# symbiotic
sea_add_symbiotic(byte_buf_eq ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  aws_byte_buf_eq_harness.c)