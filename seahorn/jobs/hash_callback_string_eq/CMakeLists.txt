add_executable(hash_callback_string_eq
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  ${AWS_C_COMMON_ROOT}/source/string.c
  ${AWS_C_COMMON_ROOT}/source/common.c
  ${AWS_C_COMMON_ROOT}/source/hash_table.c
  aws_hash_callback_string_eq_harness.c)
sea_attach_bc_link(hash_callback_string_eq)
configure_file(sea.yaml sea.yaml @ONLY)
sea_add_unsat_test(hash_callback_string_eq)
