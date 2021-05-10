add_executable(byte_buf_write_from_whole_string
  ${AWS_C_COMMON_ROOT}/source/string.c
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  aws_byte_buf_write_from_whole_string_harness.c)
sea_attach_bc_link(byte_buf_write_from_whole_string)
configure_file(sea.yaml sea.yaml @ONLY)
sea_add_unsat_test(byte_buf_write_from_whole_string)

# klee
sea_add_klee(byte_buf_write_from_whole_string
  ${AWS_C_COMMON_ROOT}/source/string.c
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
aws_byte_buf_write_from_whole_string_harness.c)

# fuzz
sea_add_fuzz(byte_buf_write_from_whole_string
  aws_byte_buf_write_from_whole_string_harness.c)

# smack
# sea_add_smack(byte_buf_write_from_whole_string 
#   ${AWS_C_COMMON_ROOT}/source/byte_buf.c
#   ${AWS_C_COMMON_ROOT}/source/string.c
#   aws_byte_buf_write_from_whole_string_harness.c)