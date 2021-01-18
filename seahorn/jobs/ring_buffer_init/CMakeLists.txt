add_executable(ring_buffer_init
  ${AWS_C_COMMON_ROOT}/source/ring_buffer.c
  aws_ring_buffer_init_harness.c)
sea_attach_bc_link(ring_buffer_init)
sea_add_unsat_test(ring_buffer_init)

# klee
sea_add_klee(ring_buffer_init
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  ${AWS_C_COMMON_ROOT}/source/ring_buffer.c
  aws_ring_buffer_init_harness.c)