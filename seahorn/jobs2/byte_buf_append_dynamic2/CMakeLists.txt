add_executable(byte_buf_append_dynamic2
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  aws_byte_buf_append_dynamic_harness2.c)
target_compile_definitions(byte_buf_append_dynamic2 PUBLIC __SEA_AWS_ALLOCATOR__)
sea_attach_bc_link(byte_buf_append_dynamic2)
configure_file(sea.yaml sea.yaml @ONLY)
sea_add_unsat_test(byte_buf_append_dynamic2)

