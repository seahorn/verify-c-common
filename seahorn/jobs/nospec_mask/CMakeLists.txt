add_executable(nospec_mask
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  aws_nospec_mask_harness.c)
sea_attach_bc_link(nospec_mask)
sea_add_unsat_test(nospec_mask)

sea_add_fuzz(nospec_mask aws_nospec_mask_harness.c)
