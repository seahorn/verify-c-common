add_executable(is_power_of_two
  aws_is_power_of_two_harness.c)
sea_attach_bc_link(is_power_of_two)
sea_add_unsat_test(is_power_of_two)

# klee
sea_add_klee(is_power_of_two
  aws_is_power_of_two_harness.c)

# smack
sea_add_smack(is_power_of_two
  aws_is_power_of_two_harness.c)

# symbiotic
sea_add_symbiotic(is_power_of_two
  aws_is_power_of_two_harness.c)