add_executable(array_list_clean_up
  ${AWS_C_COMMON_ROOT}/source/array_list.c
  aws_array_list_clean_up_harness.c)
target_compile_definitions(array_list_clean_up
  PUBLIC MAX_ITEM_SIZE=2
  MAX_INITIAL_ITEM_ALLOCATION=9223372036854775808ULL)
sea_attach_bc_link(array_list_clean_up)
sea_add_unsat_test(array_list_clean_up)

# klee
sea_add_klee(array_list_clean_up ${AWS_C_COMMON_ROOT}/source/array_list.c
<<<<<<< HEAD
aws_array_list_clean_up_harness.klee.c)
=======
aws_array_list_clean_up_harness.klee.c)
>>>>>>> 9e23b71 (test(harness): add remain bounded array list harnesses work both for klee and seahorn)
