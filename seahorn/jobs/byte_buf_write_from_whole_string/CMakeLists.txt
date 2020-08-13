add_executable(byte_buf_write_from_whole_string
  ${AWS_C_COMMON_ROOT}/source/string.c
  ${AWS_C_COMMON_ROOT}/source/byte_buf.c
  aws_byte_buf_write_from_whole_string_harness.c
  ${SEA_LIB}/proof_allocators.c
  ${SEA_LIB}/byte_buf_helper.c
  ${SEA_LIB}/string_helper.c
  ${SEA_LIB}/utils.c)
target_compile_definitions(byte_buf_write_from_whole_string PUBLIC MAX_BUFFER_SIZE=10 MAX_STRING_LEN=16)
#target_compile_definitions(byte_buf_write_from_whole_string PUBLIC HAVE_AVX3_INTRINSICS HAVE_BUILTIN_CPU_SUPPORTS HAVE_MM256_EXTRACT_EPI64 HAVE_SYSCONF USE_SIMD_ENCODING _POSIX_C_SOURCE=200809L _XOPEN_SOURCE=500 )
#set_property(TARGET byte_buf_write_from_whole_string PROPERTY C_STANDARD 99)
#set_property(TARGET byte_buf_write_from_whole_string PROPERTY C_EXTENSIONS ON)
sea_attach_bc(byte_buf_write_from_whole_string)
configure_file(sea.yaml sea.yaml @ONLY)

sea_get_file_name(BC byte_buf_write_from_whole_string.ir)
add_test(NAME byte_buf_write_from_whole_string_test COMMAND bash ${VERIFY_SCRIPT} ${BC} "unsat")

