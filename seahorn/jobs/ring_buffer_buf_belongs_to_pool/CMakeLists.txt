add_executable(
  ring_buffer_buf_belongs_to_pool
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  ${AWS_C_COMMON_ROOT}/source/ring_buffer.c
  aws_ring_buffer_buf_belongs_to_pool_harness.c
)
sea_attach_bc_link(ring_buffer_buf_belongs_to_pool)
sea_add_unsat_test(ring_buffer_buf_belongs_to_pool)

# klee
sea_add_klee(
  ring_buffer_buf_belongs_to_pool
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  ${AWS_C_COMMON_ROOT}/source/ring_buffer.c
  aws_ring_buffer_buf_belongs_to_pool_harness.c
)

# sea_add_fuzz(
#   ring_buffer_buf_belongs_to_pool
#   aws_ring_buffer_buf_belongs_to_pool_harness.c
# )

# smack
sea_add_smack(
  ring_buffer_buf_belongs_to_pool
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  ${AWS_C_COMMON_ROOT}/source/ring_buffer.c
  aws_ring_buffer_buf_belongs_to_pool_harness.c
)

# symbiotic
if(SEA_ENABLE_SYMBIOTIC)
  sea_add_symbiotic_bc(ring_buffer_buf_belongs_to_pool
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  ${AWS_C_COMMON_ROOT}/source/ring_buffer.c
  aws_ring_buffer_buf_belongs_to_pool_harness.c)
  sea_add_symbiotic_test(ring_buffer_buf_belongs_to_pool --optimize=O2)
endif()