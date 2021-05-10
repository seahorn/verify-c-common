add_executable(byte_cursor_eq_byte_buf
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  aws_byte_cursor_eq_byte_buf_harness.c)
sea_attach_bc_link(byte_cursor_eq_byte_buf)
sea_add_unsat_test(byte_cursor_eq_byte_buf)

# klee
sea_add_klee(byte_cursor_eq_byte_buf
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  aws_byte_cursor_eq_byte_buf_harness.c)

# fuzz
sea_add_fuzz(byte_cursor_eq_byte_buf aws_byte_cursor_eq_byte_buf_harness.c)

# smack
if(SEA_ENABLE_SMACK)
  sea_add_smack_bc(byte_cursor_eq_byte_buf ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  aws_byte_cursor_eq_byte_buf_harness.c)
  sea_add_smack_test(byte_cursor_eq_byte_buf --strings)
endif()