add_executable(string_bytes
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  ${AWS_C_COMMON_ROOT}/source/string.c
  ${AWS_C_COMMON_ROOT}/source/common.c
  aws_string_bytes_harness.c)
sea_attach_bc_link(string_bytes)
sea_add_unsat_test(string_bytes)

# klee
sea_add_klee(string_bytes
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  ${AWS_C_COMMON_ROOT}/source/string.c
  ${AWS_C_COMMON_ROOT}/source/common.c
  aws_string_bytes_harness.c)