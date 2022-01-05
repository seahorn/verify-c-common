add_executable(byte_cursor_right_trim_pred
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  aws_byte_cursor_right_trim_pred_harness.c)
sea_attach_bc_link(byte_cursor_right_trim_pred)
configure_file(sea.yaml sea.yaml @ONLY)
sea_add_unsat_test(byte_cursor_right_trim_pred)

# klee
sea_add_klee(byte_cursor_right_trim_pred
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  aws_byte_cursor_right_trim_pred_harness.c)

# fuzz
sea_add_fuzz(byte_cursor_right_trim_pred
  aws_byte_cursor_right_trim_pred_harness.c)

# smack
sea_add_smack(byte_cursor_right_trim_pred
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  aws_byte_cursor_right_trim_pred_harness.c)

# symbiotic
sea_add_symbiotic(byte_cursor_right_trim_pred
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  aws_byte_cursor_right_trim_pred_harness.c)