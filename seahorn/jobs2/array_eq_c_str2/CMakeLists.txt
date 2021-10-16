add_executable(array_eq_c_str2
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  aws_array_eq_c_str_harness2.c)
sea_attach_bc_link(array_eq_c_str2)

configure_file(sea.yaml sea.yaml @ONLY)
sea_add_unsat_test(array_eq_c_str2)

sea_add_fuzz(array_eq_c_str2
  aws_array_eq_c_str_harness2.c)

