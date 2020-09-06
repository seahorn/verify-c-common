add_executable(round_up_to_power_of_two_cex
  aws_round_up_to_power_of_two_cex_harness.c
  ${SEA_LIB}/utils.c)
# XXX MAX_BUFFER_SIZE is needed for utils.c
# XXX refactor utils.c to avoid this
target_compile_definitions(round_up_to_power_of_two_cex PUBLIC MAX_BUFFER_SIZE=10)
sea_attach_bc(round_up_to_power_of_two_cex)
# sea_add_unsat_test(round_up_to_power_of_two_cex)
