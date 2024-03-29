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

# fuzz
sea_add_fuzz(
  string_destroy_secure
  aws_string_destroy_secure_harness.c
)

if(SEA_ENABLE_FUZZ)
  set_tests_properties(string_destroy_secure_fuzz_test PROPERTIES WILL_FAIL TRUE)
endif()

# smack
sea_add_smack(
  string_destroy_secure
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  ${AWS_C_COMMON_ROOT}/source/string.c
  ${AWS_C_COMMON_ROOT}/source/common.c
  aws_string_destroy_secure_harness.c
)

# symbiotic
sea_add_symbiotic(
  string_destroy_secure
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  ${AWS_C_COMMON_ROOT}/source/string.c
  ${AWS_C_COMMON_ROOT}/source/common.c
  aws_string_destroy_secure_harness.c
)