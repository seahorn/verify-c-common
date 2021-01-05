add_executable(byte_buf_init
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  aws_byte_buf_init_harness.c)
target_compile_definitions(byte_buf_init
  PUBLIC KLEE_MAX_SIZE=${KLEE_MAX_SIZE} # only use for compilation
)
sea_attach_bc_link(byte_buf_init)
sea_add_unsat_test(byte_buf_init)

# klee
sea_add_klee(byte_buf_init ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  aws_byte_buf_init_harness.c)
