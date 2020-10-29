add_library(nd_fuzz nd_fuzz.c)

add_library(sea_utils utils.c)
target_compile_definitions(sea_utils PUBLIC
  MAX_BUFFER_SIZE=${MAX_BUFFER_SIZE}
  MAX_STRING_LEN=${MAX_STRING_LEN})
sea_attach_bc(sea_utils)
