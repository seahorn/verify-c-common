add_executable(
  priority_queue_clean_up
  ${AWS_C_COMMON_ROOT}/source/array_list.c
  ${AWS_C_COMMON_ROOT}/source/priority_queue.c
  aws_priority_queue_clean_up_harness.c
)
sea_attach_bc_link(priority_queue_clean_up)
sea_add_unsat_test(priority_queue_clean_up)

# klee
sea_add_klee(
  priority_queue_clean_up
  ${AWS_C_COMMON_ROOT}/source/array_list.c
  ${AWS_C_COMMON_ROOT}/source/priority_queue.c
  aws_priority_queue_clean_up_harness.c
)

# fuzz
sea_add_fuzz(
  priority_queue_clean_up
  aws_priority_queue_clean_up_harness.c
)

# smack
sea_add_smack(
  priority_queue_clean_up
  ${AWS_C_COMMON_ROOT}/source/array_list.c
  ${AWS_C_COMMON_ROOT}/source/priority_queue.c
  aws_priority_queue_clean_up_harness.c
)