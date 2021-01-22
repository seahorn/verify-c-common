add_executable(string_destroy
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  ${AWS_C_COMMON_ROOT}/source/string.c
  ${AWS_C_COMMON_ROOT}/source/common.c
  aws_string_destroy_harness.c)
sea_attach_bc_link(string_destroy)
sea_add_unsat_test(string_destroy)

# klee
sea_add_klee(string_destroy
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  ${AWS_C_COMMON_ROOT}/source/string.c
  ${AWS_C_COMMON_ROOT}/source/common.c
  aws_string_destroy_harness.c)