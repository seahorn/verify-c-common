add_executable(byte_cursor_compare_lexical
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  aws_byte_cursor_compare_lexical_harness.c)
sea_attach_bc_link(byte_cursor_compare_lexical)
sea_add_unsat_test(byte_cursor_compare_lexical)

# klee
sea_add_klee(byte_cursor_compare_lexical
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  aws_byte_cursor_compare_lexical_harness.c)

# fuzz
sea_add_fuzz(byte_cursor_compare_lexical
  aws_byte_cursor_compare_lexical_harness.c)

# smack
if(SEA_ENABLE_SMACK)
  sea_add_smack_bc(byte_cursor_compare_lexical ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  aws_byte_cursor_compare_lexical_harness.c)
  sea_add_smack_test(byte_cursor_compare_lexical --strings)
endif()

# symbiotic
sea_add_symbiotic(byte_cursor_compare_lexical ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  aws_byte_cursor_compare_lexical_harness.c)