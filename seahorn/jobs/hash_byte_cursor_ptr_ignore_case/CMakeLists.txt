add_executable(hash_byte_cursor_ptr_ignore_case
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  ${AWS_C_COMMON_ROOT}/source/hash_table.c
  aws_hash_byte_cursor_ptr_ignore_case_harness.c)
sea_attach_bc_link(hash_byte_cursor_ptr_ignore_case)
configure_file(sea.yaml sea.yaml @ONLY)
sea_add_unsat_test(hash_byte_cursor_ptr_ignore_case)

# klee
sea_add_klee(hash_byte_cursor_ptr_ignore_case
  ${AWS_C_COMMON_ROOT}/source/hash_table.c
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  aws_hash_byte_cursor_ptr_ignore_case_harness.c)

sea_add_fuzz(hash_byte_cursor_ptr_ignore_case
  aws_hash_byte_cursor_ptr_ignore_case_harness.c)
