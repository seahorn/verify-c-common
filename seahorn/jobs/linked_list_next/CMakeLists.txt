add_executable(linked_list_next
  aws_linked_list_next_harness.c)
sea_attach_bc_link(linked_list_next)
sea_add_unsat_test(linked_list_next)

# klee
sea_add_klee(linked_list_next
aws_linked_list_next_harness.c)
