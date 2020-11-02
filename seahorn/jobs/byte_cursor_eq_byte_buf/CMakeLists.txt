add_executable(byte_cursor_eq_byte_buf
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  aws_byte_cursor_eq_byte_buf_harness.c
  ${SEA_LIB}/proof_allocators.c
  ${SEA_LIB}/byte_buf_helper.c
  ${SEA_LIB}/bcmp.c
  ${SEA_LIB}/utils.c)
sea_attach_bc(byte_cursor_eq_byte_buf)
sea_add_unsat_test(byte_cursor_eq_byte_buf)

