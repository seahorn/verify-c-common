add_executable(hash_table_mem_leak
  hash_table_mem_leak.c)
sea_attach_bc_link(hash_table_mem_leak)
configure_file(sea.yaml sea.yaml @ONLY) 
sea_add_unsat_test(hash_table_mem_leak)