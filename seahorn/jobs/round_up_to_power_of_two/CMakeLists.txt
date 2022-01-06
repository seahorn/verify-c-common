add_executable(round_up_to_power_of_two
  aws_round_up_to_power_of_two_harness.c)
sea_attach_bc_link(round_up_to_power_of_two)
sea_add_unsat_test(round_up_to_power_of_two)

# klee
sea_add_klee(round_up_to_power_of_two
  aws_round_up_to_power_of_two_harness.c)

# smack
sea_add_smack(round_up_to_power_of_two
  aws_round_up_to_power_of_two_harness.c)

# symbiotic
sea_add_symbiotic(round_up_to_power_of_two
  aws_round_up_to_power_of_two_harness.c)