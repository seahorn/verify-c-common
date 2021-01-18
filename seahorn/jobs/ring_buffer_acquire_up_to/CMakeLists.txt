add_executable(ring_buffer_acquire_up_to
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  ${AWS_C_COMMON_ROOT}/source/ring_buffer.c
  aws_ring_buffer_acquire_up_to_harness.c)
sea_attach_bc_link(ring_buffer_acquire_up_to)
configure_file(sea.yaml sea.yaml @ONLY)
sea_add_unsat_test(ring_buffer_acquire_up_to)

# klee
sea_add_klee(ring_buffer_acquire_up_to
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  ${AWS_C_COMMON_ROOT}/source/ring_buffer.c
  aws_ring_buffer_acquire_up_to_harness.c)