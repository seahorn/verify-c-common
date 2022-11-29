add_executable(linked_list_back
  aws_linked_list_back_harness.c)
sea_attach_bc_link(linked_list_back)
sea_add_unsat_test(linked_list_back)
configure_file(sea.yaml sea.yaml @ONLY)

# klee
sea_add_klee(linked_list_back
  aws_linked_list_back_harness.c)

# fuzz
sea_add_fuzz(linked_list_back
  aws_linked_list_back_harness.c)

# smack
sea_add_smack(linked_list_back
  aws_linked_list_back_harness.c)

# symbiotic
sea_add_symbiotic(linked_list_back
  aws_linked_list_back_harness.c)
