add_executable(linked_list_next
  aws_linked_list_next_harness.c)
sea_attach_bc_link(linked_list_next)
sea_add_unsat_test(linked_list_next)

# klee
sea_add_klee(linked_list_next
aws_linked_list_next_harness.c)

# fuzz
sea_add_fuzz(linked_list_next
  aws_linked_list_next_harness.c)

# smack
sea_add_smack(linked_list_next
  aws_linked_list_next_harness.c)

# symbiotic
sea_add_symbiotic(linked_list_next
  aws_linked_list_next_harness.c)