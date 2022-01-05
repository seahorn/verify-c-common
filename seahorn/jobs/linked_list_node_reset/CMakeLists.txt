add_executable(linked_list_node_reset
  aws_linked_list_node_reset_harness.c)
configure_file(sea.yaml sea.yaml @ONLY)
sea_attach_bc_link(linked_list_node_reset)
sea_add_unsat_test(linked_list_node_reset)

# klee
sea_add_klee(linked_list_node_reset
  aws_linked_list_node_reset_harness.c)

# fuzz
sea_add_fuzz(linked_list_node_reset
  aws_linked_list_node_reset_harness.c)

# smack
sea_add_smack(linked_list_node_reset
  aws_linked_list_node_reset_harness.c)

# symbiotic
sea_add_symbiotic(linked_list_node_reset
  aws_linked_list_node_reset_harness.c)