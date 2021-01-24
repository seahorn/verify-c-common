add_executable(byte_buf_eq_c_str
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  aws_byte_buf_eq_c_str_harness.c)
sea_attach_bc_link(byte_buf_eq_c_str)
configure_file(sea.yaml sea.yaml @ONLY)
sea_add_unsat_test(byte_buf_eq_c_str)

sea_add_fuzz(byte_buf_eq_c_str
  aws_byte_buf_eq_c_str_harness.c)

# klee
sea_add_klee(byte_buf_eq_c_str ${AWS_C_COMMON_ROOT}/source/byte_buf.c
aws_byte_buf_eq_c_str_harness.c)
