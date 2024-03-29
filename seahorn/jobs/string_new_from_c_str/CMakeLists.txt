add_executable(
  string_new_from_c_str
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  ${AWS_C_COMMON_ROOT}/source/string.c
  ${AWS_C_COMMON_ROOT}/source/common.c
  aws_string_new_from_c_str_harness.c
)
sea_attach_bc_link(string_new_from_c_str)
configure_file(sea.yaml sea.yaml @ONLY)
sea_add_unsat_test(string_new_from_c_str)

# klee
sea_add_klee(
  string_new_from_c_str
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  ${AWS_C_COMMON_ROOT}/source/string.c
  ${AWS_C_COMMON_ROOT}/source/common.c
  aws_string_new_from_c_str_harness.c
)

# fuzz
sea_add_fuzz(
  string_new_from_c_str
  aws_string_new_from_c_str_harness.c
)

# smack
sea_add_smack(
  string_new_from_c_str
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  ${AWS_C_COMMON_ROOT}/source/string.c
  ${AWS_C_COMMON_ROOT}/source/common.c
  aws_string_new_from_c_str_harness.c
)

# symbiotic
sea_add_symbiotic(
  string_new_from_c_str
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  ${AWS_C_COMMON_ROOT}/source/string.c
  ${AWS_C_COMMON_ROOT}/source/common.c
  aws_string_new_from_c_str_harness.c
)