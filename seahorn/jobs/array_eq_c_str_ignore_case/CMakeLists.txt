add_executable(array_eq_c_str_ignore_case
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  aws_array_eq_c_str_ignore_case_harness.c)
sea_attach_bc_link(array_eq_c_str_ignore_case)
configure_file(sea.yaml sea.yaml @ONLY)
sea_add_unsat_test(array_eq_c_str_ignore_case)
