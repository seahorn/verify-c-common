add_executable(string_compare
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  ${AWS_C_COMMON_ROOT}/source/string.c
  ${AWS_C_COMMON_ROOT}/source/common.c
  aws_string_compare_harness.c)
sea_attach_bc_link(string_compare)
sea_add_unsat_test(string_compare)

# klee
sea_add_klee(string_compare
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  ${AWS_C_COMMON_ROOT}/source/string.c
  ${AWS_C_COMMON_ROOT}/source/common.c
  aws_string_compare_harness.c)