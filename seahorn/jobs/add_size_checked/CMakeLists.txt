add_executable(add_size_checked aws_add_size_checked_harness.c)
sea_attach_bc_link(add_size_checked)
sea_add_unsat_test(add_size_checked)

sea_add_fuzz(add_size_checked aws_add_size_checked_harness.c)

# klee
sea_add_klee(add_size_checked aws_add_size_checked_harness.c)

# smack
sea_add_smack(add_size_checked aws_add_size_checked_harness.c)
