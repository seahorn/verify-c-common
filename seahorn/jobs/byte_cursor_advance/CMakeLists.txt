add_executable(byte_cursor_advance
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  aws_byte_cursor_advance_harness.c)
sea_attach_bc_link(byte_cursor_advance)
sea_add_unsat_test(byte_cursor_advance)

# klee
sea_add_klee(byte_cursor_advance
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  aws_byte_cursor_advance_harness.c)

# fuzz
sea_add_fuzz(byte_cursor_advance aws_byte_cursor_advance_harness.c)

# smack
sea_add_smack(byte_cursor_advance ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  aws_byte_cursor_advance_harness.c)