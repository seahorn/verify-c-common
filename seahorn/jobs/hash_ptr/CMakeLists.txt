add_executable(hash_ptr
  ${AWS_C_COMMON_ROOT}/source/hash_table.c
  aws_hash_ptr_harness.c)
sea_attach_bc_link(hash_ptr)
sea_add_unsat_test(hash_ptr)

# klee
sea_add_klee(hash_ptr
  ${AWS_C_COMMON_ROOT}/source/hash_table.c
  aws_hash_ptr_harness.c)

sea_add_fuzz(hash_ptr aws_hash_ptr_harness.c)
