add_executable(array_eq
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  aws_array_eq_harness.c)
sea_attach_bc_link(array_eq)

configure_file(sea.yaml sea.yaml @ONLY)
sea_add_unsat_test(array_eq)

# klee
sea_add_klee(array_eq ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  aws_array_eq_harness.c)

# smack
if(SEA_ENABLE_SMACK)
  sea_add_smack_bc(array_eq ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  aws_array_eq_harness.c)
  sea_add_smack_test(array_eq --strings)
endif()

# symbiotic
sea_add_symbiotic(array_eq ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  aws_array_eq_harness.c)