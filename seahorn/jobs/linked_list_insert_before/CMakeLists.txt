add_executable(linked_list_insert_before
  aws_linked_list_insert_before_harness.c)
sea_attach_bc_link(linked_list_insert_before)
sea_add_unsat_test(linked_list_insert_before)

# klee
sea_add_klee(linked_list_insert_before
  aws_linked_list_insert_before_harness.c)

# fuzz
sea_add_fuzz(linked_list_insert_before
  aws_linked_list_insert_before_harness.c)

# smack
sea_add_smack(linked_list_insert_before
  aws_linked_list_insert_before_harness.c)