add_executable(byte_buf_eq_ignore_case2
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  aws_byte_buf_eq_ignore_case_harness2.c)
sea_attach_bc_link(byte_buf_eq_ignore_case2)
configure_file(sea.yaml sea.yaml @ONLY)
sea_add_unsat_test(byte_buf_eq_ignore_case2)

# fuzz
sea_add_fuzz(byte_buf_eq_ignore_case2
  aws_byte_buf_eq_ignore_case_harness2.c)

# smack
sea_add_smack(byte_buf_eq_ignore_case2 ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  aws_byte_buf_eq_ignore_case_harness2.c)