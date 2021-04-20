# various upper bounds from config.h.in
add_library(sea_bounds bounds.c)
sea_attach_bc(sea_bounds)

# proof helpers
add_library(
  sea_proofs
  array_list_helper.c
  byte_buf_helper.c
  linked_list_helper.c
  string_helper.c
  priority_queue_helper.c
  ring_buffer_helper.c
  hash_table_helper.c
  utils.c
  proof_allocators.c
  sea_allocators.c
  allocator_override.c
  bcmp.c
  error_override.c
)
if(SEA_ALLOCATOR_CAN_FAIL)
  target_compile_definitions(sea_proofs PRIVATE SEA_ALLOCATOR_CAN_FAIL)
endif()
sea_attach_bc(sea_proofs)

# string proof helpers
add_library(str_proofs sea_string.cc)

sea_attach_bc_cc(str_proofs)

# symbolic execution (klee) helpers
if(SEA_ENABLE_KLEE)
  set(SEA_SCPT ${CMAKE_SOURCE_DIR}/seahorn/scripts)
  add_custom_target(
    klee_malloc ALL
    COMMAND python3 ${SEA_SCPT}/create_alloce_size_switch.py -path ${SEA_LIB} -size ${KLEE_MAX_SIZE}
  )
endif()

add_library(
  sea_symex
  klee_array_list_helper.c
  klee_byte_buf_helper.c
  linked_list_helper.c
  klee_string_helper.c
  klee_priority_queue_helper.c
  utils.c
  klee_ring_buffer_helper.c
  klee_allocators.c
  klee_hash_table_helper.c
  sea_allocators.c
  allocator_override.c
  sea_string.cc
  error_override.c
  nd_klee.c
  klee_switch.c
)
target_compile_definitions(sea_symex PRIVATE __KLEE__)
sea_attach_bc(sea_symex)

add_library(
  sea_fuzz
  nd_fuzz.c
  fuzz_allocators.c
  fuzz_array_list_helper.c
  fuzz_byte_buf_helper.c
  fuzz_string_helper.c
  fuzz_priority_queue_helper.c
  fuzz_ring_buffer_helper.c
  fuzz_hash_table_helper.c
  bounds.c
  utils.c
  sea_allocators.c
)
target_compile_options(sea_fuzz PUBLIC -fdeclspec -fsanitize=fuzzer-no-link,address,undefined -fprofile-instr-generate -fcoverage-mapping)
