add_executable(byte_cursor_eq_c_str
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  aws_byte_cursor_eq_c_str_harness.c)
sea_attach_bc_link(byte_cursor_eq_c_str)
configure_file(sea.yaml sea.yaml @ONLY)
sea_add_unsat_test(byte_cursor_eq_c_str)

# klee
sea_add_klee(byte_cursor_eq_c_str
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  aws_byte_cursor_eq_c_str_harness.c)

# fuzz
sea_add_fuzz(byte_cursor_eq_c_str
  aws_byte_cursor_eq_c_str_harness.c)

# smack
sea_add_smack(byte_cursor_eq_c_str
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  aws_byte_cursor_eq_c_str_harness.c)

# symbiotic
sea_add_symbiotic(byte_cursor_eq_c_str
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  aws_byte_cursor_eq_c_str_harness.c)