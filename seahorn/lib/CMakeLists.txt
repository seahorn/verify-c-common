# various upper bounds
add_library(sea_bounds bounds.c)
target_compile_definitions(sea_bounds PUBLIC
  MAX_BUFFER_SIZE=${MAX_BUFFER_SIZE}
  MAX_STRING_LEN=${MAX_STRING_LEN}
  MAX_INITIAL_SIZE=${MAX_INITIAL_SIZE}
  MAX_ITEM_SIZE=${MAX_ITEM_SIZE}
  MAX_INITIAL_ITEM_ALLOCATION=${MAX_INITIAL_ITEM_ALLOCATION})
sea_attach_bc(sea_bounds)

# proof helpers
add_library(sea_proofs
  array_list_helper.c
  byte_buf_helper.c
  linked_list_helper.c
  string_helper.c
  utils.c
  proof_allocators.c
  sea_allocators.c
  allocator_override.c
  bcmp.c
  sea_string.c
  error_override.c)

target_compile_definitions(sea_proofs PUBLIC
  MAX_BUFFER_SIZE=${MAX_BUFFER_SIZE}
  MAX_STRING_LEN=${MAX_STRING_LEN})
sea_attach_bc(sea_proofs)

if(SEA_ENABLE_KLEE)
  set(SEA_SCPT ${CMAKE_SOURCE_DIR}/seahorn/scripts)
  add_custom_target(klee_malloc ALL
    COMMAND python3 ${SEA_SCPT}/create_alloce_size_switch.py -path ${SEA_LIB} -size ${MAX_BUFFER_SIZE})
endif()

add_library(sea_symex
  klee_array_list_helper.c
  byte_buf_helper.c
  linked_list_helper.c
  klee_string_helper.c
  utils.c
  klee_allocators.c
  sea_allocators.c
  allocator_override.c
  sea_string.c
  error_override.c
  nd_klee.c
  klee_switch.c
  )
target_compile_definitions(sea_symex PUBLIC
  MAX_BUFFER_SIZE=${MAX_BUFFER_SIZE}
  MAX_STRING_LEN=${MAX_STRING_LEN})
sea_attach_bc(sea_symex)

add_library(sea_fuzz
  nd_fuzz.c
  fuzz_allocators.c
  fuzz_string_helper.c
  bounds.c
  utils.c
  )
target_compile_options(sea_fuzz PUBLIC -fdeclspec)
