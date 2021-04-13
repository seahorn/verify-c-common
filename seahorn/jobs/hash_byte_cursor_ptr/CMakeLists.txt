add_executable(hash_byte_cursor_ptr
  ${AWS_C_COMMON_ROOT}/source/hash_table.c
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  aws_hash_byte_cursor_ptr_harness.c)
sea_attach_bc_link(hash_byte_cursor_ptr)
configure_file(sea.yaml sea.yaml @ONLY)
sea_add_unsat_test(hash_byte_cursor_ptr)

# klee
sea_add_klee(hash_byte_cursor_ptr
  ${AWS_C_COMMON_ROOT}/source/hash_table.c
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  aws_hash_byte_cursor_ptr_harness.c)

sea_add_fuzz(hash_byte_cursor_ptr
  aws_hash_byte_cursor_ptr_harness.c)
