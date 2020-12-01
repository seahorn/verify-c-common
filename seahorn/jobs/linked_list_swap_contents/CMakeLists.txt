# add head and tail to list size.
add_executable(linked_list_swap_contents
  aws_linked_list_swap_contents_harness.c)
sea_attach_bc_link(linked_list_swap_contents)
sea_add_unsat_test(linked_list_swap_contents)

# klee
sea_add_klee(linked_list_swap_contents
aws_linked_list_swap_contents_harness.c)
