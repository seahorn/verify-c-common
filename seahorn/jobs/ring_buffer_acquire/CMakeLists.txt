add_executable(
  ring_buffer_acquire
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  ${AWS_C_COMMON_ROOT}/source/ring_buffer.c
  aws_ring_buffer_acquire_harness.c
)
sea_attach_bc_link(ring_buffer_acquire)
sea_add_unsat_test(ring_buffer_acquire)

# klee
sea_add_klee(
  ring_buffer_acquire
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  ${AWS_C_COMMON_ROOT}/source/ring_buffer.c
  aws_ring_buffer_acquire_harness.c
)

# fuzz
sea_add_fuzz(
  ring_buffer_acquire
  aws_ring_buffer_acquire_harness.c
)

# smack
sea_add_smack(
  ring_buffer_acquire
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  ${AWS_C_COMMON_ROOT}/source/ring_buffer.c
  aws_ring_buffer_acquire_harness.c
)

# symbiotic
if(SEA_ENABLE_SYMBIOTIC)
  sea_add_symbiotic_bc(ring_buffer_acquire
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  ${AWS_C_COMMON_ROOT}/source/ring_buffer.c
  aws_ring_buffer_acquire_harness.c)
  sea_add_symbiotic_test(ring_buffer_acquire --optimize=O2)
endif()