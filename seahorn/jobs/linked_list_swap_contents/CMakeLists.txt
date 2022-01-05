# add head and tail to list size.
add_executable(linked_list_swap_contents
  aws_linked_list_swap_contents_harness.c)
sea_attach_bc_link(linked_list_swap_contents)
sea_add_unsat_test(linked_list_swap_contents)

# klee
sea_add_klee(linked_list_swap_contents
  aws_linked_list_swap_contents_harness.c)

# fuzz
sea_add_fuzz(linked_list_swap_contents
  aws_linked_list_swap_contents_harness.c)

# smack
sea_add_smack(linked_list_swap_contents
  aws_linked_list_swap_contents_harness.c)

# symbiotic
sea_add_symbiotic(linked_list_swap_contents
  aws_linked_list_swap_contents_harness.c)