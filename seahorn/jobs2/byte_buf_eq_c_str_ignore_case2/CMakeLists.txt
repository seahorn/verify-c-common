add_executable(byte_buf_eq_c_str_ignore_case2
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  aws_byte_buf_eq_c_str_ignore_case_harness2.c)
configure_file(sea.yaml sea.yaml @ONLY)
sea_attach_bc_link(byte_buf_eq_c_str_ignore_case2)
sea_add_unsat_test(byte_buf_eq_c_str_ignore_case2)

