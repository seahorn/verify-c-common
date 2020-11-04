add_library(nd_fuzz nd_fuzz.c)

add_library(sea_utils utils.c)
target_compile_definitions(sea_utils PUBLIC
  MAX_BUFFER_SIZE=${MAX_BUFFER_SIZE}
  MAX_STRING_LEN=${MAX_STRING_LEN})
sea_attach_bc(sea_utils)

# various upper bounds
add_library(sea_bounds bounds.c)
target_compile_definitions(sea_bounds PUBLIC
  MAX_BUFFER_SIZE=${MAX_BUFFER_SIZE}
  MAX_STRING_LEN=${MAX_STRING_LEN})
sea_attach_bc(sea_bounds)

# proof helpers
add_library(sea_proofs
  array_list_helper.c
  byte_buf_helper.c
  linked_list_helper.c
  string_helper.c
  utils.c
  proof_allocators.c
  #sea_allocators.c
  #allocator_override.c
  bcmp.c
  #sea_string.c
  #error_override.c
  )

target_compile_definitions(sea_proofs PUBLIC
  MAX_BUFFER_SIZE=${MAX_BUFFER_SIZE}
  MAX_STRING_LEN=${MAX_STRING_LEN})
target_compile_definitions(sea_proofs PRIVATE NBOUNDS)
sea_attach_bc(sea_proofs)

