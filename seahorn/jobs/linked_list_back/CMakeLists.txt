add_executable(linked_list_back
    aws_linked_list_back_harness.c
    ${SEA_LIB}/proof_allocators.c
    ${SEA_LIB}/linked_list_helper.c)
target_compile_definitions(linked_list_back
    PUBLIC __SEA_AWS_ALLOCATOR__ __SEA_AWS_REAL_ALLOCATOR__)
sea_attach_bc(linked_list_back)
sea_add_unsat_test(linked_list_back)


