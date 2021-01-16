add_executable(byte_buf_cat
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  aws_byte_buf_cat_harness.c)
sea_attach_bc_link(byte_buf_cat)
sea_add_unsat_test(byte_buf_cat)
# VARARGS are not supported causing this test to fail
set_tests_properties(byte_buf_cat_unsat_test PROPERTIES WILL_FAIL ON)

# klee
# Klee will get timeout on this test
# sea_add_klee(byte_buf_cat ${AWS_C_COMMON_ROOT}/source/byte_buf.c
#   aws_byte_buf_cat_harness.c)