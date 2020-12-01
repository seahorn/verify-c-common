add_executable(ring_buffer_release
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  ${AWS_C_COMMON_ROOT}/source/ring_buffer.c
  aws_ring_buffer_release_harness.c)
sea_attach_bc_link(ring_buffer_release)
configure_file(sea.yaml sea.yaml @ONLY)
sea_add_unsat_test(ring_buffer_release)
