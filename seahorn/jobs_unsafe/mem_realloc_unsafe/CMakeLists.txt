add_executable(mem_realloc_unsafe
  ${AWS_C_COMMON_ROOT}/source/allocator.c
  ${SEA_LIB}/bcmp.c
  ${SEA_LIB}/proof_allocators.c
  ${SEA_LIB}/sea_allocators.c
  aws_mem_realloc_unsafe_harness.c)

sea_link_libraries(mem_realloc_unsafe sea_bounds.ir)
sea_attach_bc(mem_realloc_unsafe)
sea_add_sat_test(mem_realloc_unsafe)