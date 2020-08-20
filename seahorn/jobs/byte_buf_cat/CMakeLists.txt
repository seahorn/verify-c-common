add_executable(byte_buf_cat
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  aws_byte_buf_cat_harness.c
  ${SEA_LIB}/proof_allocators.c
  ${SEA_LIB}/byte_buf_helper.c
  ${SEA_LIB}/bcmp.c
  ${SEA_LIB}/utils.c)
target_compile_definitions(byte_buf_cat PUBLIC MAX_BUFFER_SIZE=10 __SEA_AWS_ALLOCATOR__)
sea_attach_bc(byte_buf_cat)
sea_add_unsat_test(byte_buf_cat)
# VARARGS are not supported causing this test to fail
set_tests_properties(byte_buf_cat_unsat_test PROPERTIES WILL_FAIL ON)
