add_executable(hash_string
  ${AWS_C_COMMON_ROOT}/source/string.c
  aws_hash_string_harness.c)
sea_link_libraries(hash_string hash_table.opt.ir)
sea_attach_bc_link(hash_string)
sea_add_unsat_test(hash_string)