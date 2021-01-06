add_executable(hash_array_ignore_case
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  aws_hash_array_ignore_case_harness.c)
sea_link_libraries(hash_array_ignore_case hash_table.opt.ir)
sea_attach_bc_link(hash_array_ignore_case)
sea_add_unsat_test(hash_array_ignore_case)