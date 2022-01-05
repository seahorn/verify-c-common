add_executable(byte_buf_eq_c_str_ignore_case
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  aws_byte_buf_eq_c_str_ignore_case_harness.c)
configure_file(sea.yaml sea.yaml @ONLY)
sea_attach_bc_link(byte_buf_eq_c_str_ignore_case)
sea_add_unsat_test(byte_buf_eq_c_str_ignore_case)

# klee
sea_add_klee(byte_buf_eq_c_str_ignore_case ${AWS_C_COMMON_ROOT}/source/byte_buf.c
aws_byte_buf_eq_c_str_ignore_case_harness.c)

# fuzz
sea_add_fuzz(byte_buf_eq_c_str_ignore_case
  aws_byte_buf_eq_c_str_ignore_case_harness.c)

# smack
sea_add_smack(byte_buf_eq_c_str_ignore_case ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  aws_byte_buf_eq_c_str_ignore_case_harness.c)

# symbiotic
sea_add_symbiotic(byte_buf_eq_c_str_ignore_case ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  aws_byte_buf_eq_c_str_ignore_case_harness.c)