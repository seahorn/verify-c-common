add_executable(hash_byte_cursor_ptr
  ${AWS_C_COMMON_ROOT}/source/hash_table.c
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  aws_hash_byte_cursor_ptr_harness.c)
target_compile_definitions(hash_byte_cursor_ptr
  PUBLIC MAX_CURSOR_SIZE=32)
sea_attach_bc_link(hash_byte_cursor_ptr)
sea_add_unsat_test(hash_byte_cursor_ptr)