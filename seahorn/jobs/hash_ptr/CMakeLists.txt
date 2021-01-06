add_executable(hash_ptr
  aws_hash_ptr_harness.c)
sea_link_libraries(hash_ptr hash_table.opt.ir)
sea_attach_bc_link(hash_ptr)
sea_add_unsat_test(hash_ptr)