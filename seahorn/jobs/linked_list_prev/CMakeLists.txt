add_executable(linked_list_prev
  aws_linked_list_prev_harness.c)
sea_attach_bc_link(linked_list_prev)
sea_add_unsat_test(linked_list_prev)

# klee
sea_add_klee(linked_list_prev
aws_linked_list_prev_harness.c)
