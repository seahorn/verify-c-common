add_executable(linked_list_front
  aws_linked_list_front_harness.c)
sea_attach_bc_link(linked_list_front)
sea_add_unsat_test(linked_list_front)

# klee
sea_add_klee(linked_list_front
  aws_linked_list_front_harness.c)
