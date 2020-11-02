add_executable(round_up_to_power_of_two
  aws_round_up_to_power_of_two_harness.c
  ${SEA_LIB}/utils.c)
sea_attach_bc(round_up_to_power_of_two)
sea_add_unsat_test(round_up_to_power_of_two)
