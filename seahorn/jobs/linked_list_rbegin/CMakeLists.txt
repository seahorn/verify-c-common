# add head and tail to list size.
add_executable(linked_list_rbegin
  aws_linked_list_rbegin_harness.c)
target_compile_definitions(linked_list_rbegin
  # We will use our own function for is_valid check hence AWS_DEEP_CHECK is off
  PUBLIC SEA_DEEP_CHECKS=0)
sea_attach_bc_link(linked_list_rbegin)
sea_add_unsat_test(linked_list_rbegin)
configure_file(sea.yaml sea.yaml @ONLY)

# klee
sea_add_klee(linked_list_rbegin
  aws_linked_list_rbegin_harness.c)

# fuzz
sea_add_fuzz(linked_list_rbegin
  aws_linked_list_rbegin_harness.c)

# smack
sea_add_smack(linked_list_rbegin
  aws_linked_list_rbegin_harness.c)

# symbiotic
sea_add_symbiotic(linked_list_rbegin
  aws_linked_list_rbegin_harness.c)