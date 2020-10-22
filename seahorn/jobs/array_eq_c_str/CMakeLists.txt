add_executable(array_eq_c_str
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  ${AWS_C_COMMON_ROOT}/source/error.c
  ${AWS_C_COMMON_ROOT}/source/assert.c
  ${AWS_C_COMMON_ROOT}/source/common.c
  ${AWS_C_COMMON_ROOT}/source/array_list.c
  ${AWS_C_COMMON_ROOT}/source/allocator.c
  ${AWS_C_COMMON_ROOT}/source/logging.c
  ${AWS_C_COMMON_ROOT}/source/log_formatter.c
  ${AWS_C_COMMON_ROOT}/source/log_channel.c
  ${AWS_C_COMMON_ROOT}/source/log_writer.c
  ${AWS_C_COMMON_ROOT}/source/string.c
  ${AWS_C_COMMON_ROOT}/source/date_time.c
  ${AWS_C_COMMON_ROOT}/source/condition_variable.c
  ${AWS_C_COMMON_ROOT}/source/posix/system_info.c
  ${AWS_C_COMMON_ROOT}/source/posix/mutex.c
  ${AWS_C_COMMON_ROOT}/source/posix/thread.c
  ${AWS_C_COMMON_ROOT}/source/posix/time.c
  ${AWS_C_COMMON_ROOT}/source/posix/condition_variable.c
  aws_array_eq_c_str_harness.c
  ${SEA_LIB}/proof_allocators.c
  ${SEA_LIB}/utils.c)
set(MAX_BUFFER_SIZE 10)
target_compile_definitions(array_eq_c_str PUBLIC MAX_BUFFER_SIZE=${MAX_BUFFER_SIZE})
sea_attach_bc(array_eq_c_str)
configure_file(sea.yaml sea.yaml @ONLY)
sea_add_unsat_test(array_eq_c_str)

sea_attach_fuzz(array_eq_c_str)