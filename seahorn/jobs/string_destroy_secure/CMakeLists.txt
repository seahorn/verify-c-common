add_executable(
  string_destroy_secure
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  ${AWS_C_COMMON_ROOT}/source/string.c
  ${AWS_C_COMMON_ROOT}/source/common.c
  aws_string_destroy_secure_harness.c
)
sea_attach_bc_link(string_destroy_secure)
configure_file(sea.yaml sea.yaml @ONLY)
sea_add_unsat_test(string_destroy_secure)
# requires inline asm support

# klee
sea_add_klee(
  string_destroy_secure
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  ${AWS_C_COMMON_ROOT}/source/string.c
  ${AWS_C_COMMON_ROOT}/source/common.c
  aws_string_destroy_secure_harness.c
)


sea_add_fuzz(
  string_destroy_secure
  aws_string_destroy_secure_harness.c
)
