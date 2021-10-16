add_executable(array_eq2
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  aws_array_eq_harness2.c)
sea_attach_bc_link(array_eq2)

configure_file(sea.yaml sea.yaml @ONLY)
sea_add_unsat_test(array_eq2)

