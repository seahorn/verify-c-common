# add head and tail to list size.
add_executable(linked_list_push_back
        aws_linked_list_push_back_harness.c
        ${SEA_LIB}/linked_list_helper.c
        ${SEA_LIB}/proof_allocators.c)
target_compile_definitions(linked_list_push_back
        PUBLIC __SEA_AWS_ALLOCATOR__ __SEA_AWS_REAL_ALLOCATOR__)
sea_attach_bc(linked_list_push_back)
sea_add_unsat_test(linked_list_push_back)


