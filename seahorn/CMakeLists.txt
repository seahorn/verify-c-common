function(sea_llvm_link name)
  set(options)
  set(oneValueArgs)
  set(multiValueArgs LINK OVERRIDE)
  cmake_parse_arguments(LLVMIR_ATTACH
    "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

  if(NOT LLVMIR_ATTACH_LINK)
    message(FATAL_ERROR "sea_llvm_link: missing LINK option")
  endif()

  set(LLVMIR_TARGETS ${LLVMIR_ATTACH_LINK})
  set(LLVMIR_OVERRIDE_TARGETS ${LLVMIR_ATTACH_OVERRIDE})

  set(TRGT ${name})
  # use the first target as the main dependency
  list(GET LLVMIR_TARGETS 0 DEPENDS_TRGT)


    ## preamble
  foreach(IR ${LLVMIR_TARGETS})
    llvmir_check_target_properties(${IR})
  endforeach()

  set(OUT_LLVMIR_FILES "")
  set(FULL_OUT_LLVMIR_FILES "")

  get_property(IN_LLVMIR_TYPE TARGET ${DEPENDS_TRGT} PROPERTY LLVMIR_TYPE)
  get_property(LLVMIR_EXTERNAL_TYPE TARGET ${DEPENDS_TRGT}
    PROPERTY LLVMIR_EXTERNAL_TYPE)
  get_property(INFILES TARGET ${DEPENDS_TRGT} PROPERTY LLVMIR_FILES)
  get_property(IN_LLVMIR_DIR TARGET ${DEPENDS_TRGT} PROPERTY LLVMIR_DIR)
  get_property(LINKER_LANGUAGE TARGET ${DEPENDS_TRGT} PROPERTY LINKER_LANGUAGE)
  get_property(LINK_DEPENDS TARGET ${DEPENDS_TRGT} PROPERTY LINK_DEPENDS)
  get_property(LINK_FLAGS TARGET ${DEPENDS_TRGT} PROPERTY LINK_FLAGS)
  get_property(LINK_FLAGS_${CMAKE_BUILD_TYPE}
    TARGET ${DEPENDS_TRGT}
    PROPERTY LINK_FLAGS_${CMAKE_BUILD_TYPE})
  get_property(INTERFACE_LINK_LIBRARIES
    TARGET ${DEPENDS_TRGT}
    PROPERTY INTERFACE_LINK_LIBRARIES)
  get_property(LINK_LIBRARIES TARGET ${DEPENDS_TRGT} PROPERTY LINK_LIBRARIES)
  get_property(LINK_INTERFACE_LIBRARIES
    TARGET ${DEPENDS_TRGT}
    PROPERTY LINK_INTERFACE_LIBRARIES)
  get_property(LINK_INTERFACE_LIBRARIES_${CMAKE_BUILD_TYPE}
    TARGET ${DEPENDS_TRGT}
    PROPERTY LINK_INTERFACE_LIBRARIES_${CMAKE_BUILD_TYPE})
  get_property(SHORT_NAME TARGET ${DEPENDS_TRGT} PROPERTY LLVMIR_SHORT_NAME)

  if(NOT "${IN_LLVMIR_TYPE}" STREQUAL "${LLVMIR_BINARY_TYPE}")
    message(FATAL_ERROR "Cannot attach ${TRGT} to a ${IN_LLVMIR_TYPE} target.")
  endif()

  ## main operations
  set(WORK_DIR "${CMAKE_CURRENT_BINARY_DIR}/${LLVMIR_DIR}/${TRGT}")
  file(MAKE_DIRECTORY ${WORK_DIR})

  set(IN_FULL_LLVMIR_FILES "")
  foreach(IR ${LLVMIR_TARGETS})
    get_property(INFILES TARGET ${IR} PROPERTY LLVMIR_FILES)
    get_property(IN_LLVMIR_DIR TARGET ${IR} PROPERTY LLVMIR_DIR)
    foreach(IN_LLVMIR_FILE ${INFILES})
      list(APPEND IN_FULL_LLVMIR_FILES "${IN_LLVMIR_DIR}/${IN_LLVMIR_FILE}")
    endforeach()
  endforeach()

  get_property(IN_LLVMIR_LINK TARGET ${DEPENDS_TRGT} PROPERTY LLVMIR_LINK)
  foreach(IR ${IN_LLVMIR_LINK})
    get_property(INFILES TARGET ${IR} PROPERTY LLVMIR_FILES)
    get_property(IN_LLVMIR_DIR TARGET ${IR} PROPERTY LLVMIR_DIR)
    foreach(IN_LLVMIR_FILE ${INFILES})
      list(APPEND IN_FULL_LLVMIR_FILES "${IN_LLVMIR_DIR}/${IN_LLVMIR_FILE}")
    endforeach()
  endforeach()


  set(IN_FULL_LLVMIR_OVERIDE_FILES "")
  foreach(IR ${LLVMIR_OVERRIDE_TARGETS})
    get_property(INFILES TARGET ${IR} PROPERTY LLVMIR_FILES)
    get_property(IN_LLVMIR_DIR TARGET ${IR} PROPERTY LLVMIR_DIR)
    foreach(IN_LLVMIR_FILE ${INFILES})
      list(APPEND IN_FULL_LLVMIR_OVERRIDE_FILES "${IN_LLVMIR_DIR}/${IN_LLVMIR_FILE}")
    endforeach()
  endforeach()

  get_property(IN_LLVMIR_OVERRIDE TARGET ${DEPENDS_TRGT} PROPERTY LLVMIR_OVERRIDE)
  foreach(IR ${IN_LLVMIR_OVERRIDE})
    get_property(INFILES TARGET ${IR} PROPERTY LLVMIR_FILES)
    get_property(IN_LLVMIR_DIR TARGET ${IR} PROPERTY LLVMIR_DIR)
    foreach(IN_LLVMIR_FILE ${INFILES})
      list(APPEND IN_FULL_LLVMIR_OVERRIDE_FILES "${IN_LLVMIR_DIR}/${IN_LLVMIR_FILE}")
    endforeach()
  endforeach()

  set(IN_OVERRIDE_OPTIONS ${IN_FULL_LLVMIR_OVERRIDE_FILES})
  list(TRANSFORM IN_OVERRIDE_OPTIONS PREPEND "--override=" )

  set(FULL_OUT_LLVMIR_FILE "${WORK_DIR}/${TRGT}.${LLVMIR_BINARY_FMT_SUFFIX}")
  if(SHORT_NAME)
    set(FULL_OUT_LLVMIR_FILE
      "${WORK_DIR}/${SHORT_NAME}.${LLVMIR_BINARY_FMT_SUFFIX}")
  endif()
  get_filename_component(OUT_LLVMIR_FILE ${FULL_OUT_LLVMIR_FILE} NAME)

  list(APPEND OUT_LLVMIR_FILES ${OUT_LLVMIR_FILE})
  list(APPEND FULL_OUT_LLVMIR_FILES ${FULL_OUT_LLVMIR_FILE})

  # setup custom target
  add_custom_target(${TRGT} DEPENDS ${FULL_OUT_LLVMIR_FILES})

  set_property(TARGET ${TRGT} PROPERTY LLVMIR_TYPE ${LLVMIR_BINARY_TYPE})
  set_property(TARGET ${TRGT}
    PROPERTY LLVMIR_EXTERNAL_TYPE ${LLVMIR_EXTERNAL_TYPE})
  set_property(TARGET ${TRGT} PROPERTY LLVMIR_DIR ${WORK_DIR})
  set_property(TARGET ${TRGT} PROPERTY LLVMIR_FILES ${OUT_LLVMIR_FILES})
  set_property(TARGET ${TRGT} PROPERTY LINKER_LANGUAGE ${LINKER_LANGUAGE})
  set_property(TARGET ${TRGT} PROPERTY LINK_DEPENDS ${LINK_DEPENDS})
  set_property(TARGET ${TRGT} PROPERTY LINK_FLAGS ${LINK_FLAGS})
  set_property(TARGET ${TRGT}
    PROPERTY LINK_FLAGS_${CMAKE_BUILD_TYPE} ${LINK_FLAGS_${CMAKE_BUILD_TYPE}})
  set_property(TARGET ${TRGT}
    PROPERTY INTERFACE_LINK_LIBRARIES ${INTERFACE_LINK_LIBRARIES})
  set_property(TARGET ${TRGT}
    PROPERTY LINK_INTERFACE_LIBRARIES ${LINK_INTERFACE_LIBRARIES})
  set_property(TARGET ${TRGT}
    PROPERTY
    LINK_INTERFACE_LIBRARIES_${CMAKE_BUILD_TYPE}
    ${LINK_INTERFACE_LIBRARIES_${CMAKE_BUILD_TYPE}})
  set_property(TARGET ${TRGT} PROPERTY EXCLUDE_FROM_ALL OFF)
  set_property(TARGET ${TRGT} PROPERTY LLVMIR_SHORT_NAME ${SHORT_NAME})

  add_custom_command(OUTPUT ${FULL_OUT_LLVMIR_FILE}
    COMMAND ${LLVMIR_LINK}
    ARGS
    ${LLVMIR_ATTACH_UNPARSED_ARGUMENTS}
    -o ${FULL_OUT_LLVMIR_FILE} ${IN_FULL_LLVMIR_FILES} ${IN_OVERRIDE_OPTIONS}
    DEPENDS ${IN_FULL_LLVMIR_FILES} ${IN_FULL_LLVMIR_OVERRIDE_FILES}
    COMMENT "Linking LLVM bitcode ${OUT_LLVMIR_FILE}"
    VERBATIM)

  ## postamble
endfunction()


function(sea_link_libraries target)
  set_property(TARGET ${target} APPEND PROPERTY LLVMIR_LINK ${ARGN})
endfunction()
function(sea_overlink_libraries target)
  set_property(TARGET ${target} APPEND PROPERTY LLVMIR_OVERRIDE ${ARGN})
endfunction()

function(sea_attach_bc name)
  set(options)
  set(oneValueArgs LINKER_LANGUAGE)
  set(multiValueArgs)
  cmake_parse_arguments(ARGS
    "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

  if (NOT ARGS_LINKER_LANGUAGE)
    set(ARGS_LINKER_LANGUAGE "C")
  endif()

  set(SOURCE_EXE ${name})
  set(TARGET_BC "${SOURCE_EXE}.ir")
  set(TARGET_OBJ "${SOURCE_EXE}.obj")

  # setup target with the options that we need
  set_target_properties(${SOURCE_EXE} PROPERTIES LINKER_LANGUAGE ${ARGS_LINKER_LANGUAGE})
  target_compile_options(${SOURCE_EXE} PUBLIC -O1 -Xclang -disable-llvm-optzns)
  target_compile_options(${SOURCE_EXE} PUBLIC -Wno-macro-redefined)
  target_compile_options(${SOURCE_EXE} PUBLIC -g)
  target_compile_options(${SOURCE_EXE} PUBLIC -fdeclspec)
  set_property(TARGET ${SOURCE_EXE} PROPERTY EXCLUDE_FROM_ALL ON)

  target_compile_definitions(${SOURCE_EXE} PRIVATE __SEAHORN__)
  target_compile_definitions(${SOURCE_EXE} PRIVATE VACCHECK)

  # convert ${SOURCE_EXE} target to llvm
  llvmir_attach_bc_target(TARGET ${TARGET_OBJ} DEPENDS ${SOURCE_EXE})
  set_property(TARGET ${TARGET_OBJ} PROPERTY EXCLUDE_FROM_ALL ON)

  get_property(IN_LLVMIR_LINK TARGET ${SOURCE_EXE} PROPERTY LLVMIR_LINK)
  get_property(IN_LLVMIR_OVERRIDE TARGET ${SOURCE_EXE} PROPERTY LLVMIR_OVERRIDE)
  set_property(TARGET ${TARGET_OBJ} PROPERTY LLVMIR_LINK ${IN_LLVMIR_LINK})
  set_property(TARGET ${TARGET_OBJ} PROPERTY LLVMIR_OVERRIDE ${IN_LLVMIR_OVERRIDE})
  # link all files of ${TARGET_OBJ} together
  # llvmir_attach_link_target(TARGET ${TARGET_BC} DEPENDS ${TARGET_OBJ})
  sea_llvm_link(${TARGET_BC} LINK ${TARGET_OBJ})
  add_dependencies(${TARGET_BC} ${TARGET_OBJ})

  set_property(TARGET ${TARGET_BC} PROPERTY EXCLUDE_FROM_ALL OFF)
endfunction()

# for C++ code
function(sea_attach_bc_cc name)
  sea_attach_bc(${name} LINKER_LANGUAGE CXX)
endfunction()

function(sea_get_file_name VAR LLVMIR_TARGET)
  get_property(DIR TARGET ${LLVMIR_TARGET} PROPERTY LLVMIR_DIR)
  get_property(FILES TARGET ${LLVMIR_TARGET} PROPERTY LLVMIR_FILES)
  set(${VAR} "${DIR}/${FILES}" PARENT_SCOPE)
endfunction()

macro(sea_add_fuzz_executable name)
  cmake_parse_arguments(ARG
    "EXCLUDE_FROM_ALL" "" "" ${ARGN})

  set(EXE_NAME "${name}_fuzz")

  add_executable(${EXE_NAME} ${ARG_UNPARSED_ARGUMENTS})

  target_compile_options(${EXE_NAME} PRIVATE -Wno-macro-redefined)
  target_compile_options(${EXE_NAME} PRIVATE -g)
  target_compile_options(${EXE_NAME} PRIVATE -fdeclspec)

  target_compile_options(${EXE_NAME} PRIVATE -ggdb3 -fno-omit-frame-pointer
    -fprofile-instr-generate -fcoverage-mapping)
  target_compile_definitions(${EXE_NAME} PRIVATE main=_main)
  target_compile_definitions(${EXE_NAME} PRIVATE MAX_BUFFER_SIZE=${MAX_BUFFER_SIZE})

  target_link_libraries(${EXE_NAME} PRIVATE AWS::aws-c-common )
  target_link_libraries(${EXE_NAME} PRIVATE sea_fuzz)

  target_compile_options(${EXE_NAME} PRIVATE -fsanitize=fuzzer,address,undefined)
  target_link_libraries(${EXE_NAME} PRIVATE -fsanitize=fuzzer,address,undefined
    -fprofile-instr-generate -fcoverage-mapping)
endmacro()

function(sea_attach_bc_link name)
  sea_link_libraries(${name} sea_proofs.ir sea_bounds.ir str_proofs.ir)
  sea_attach_bc(${name})
endfunction()

function(klee_attach_bc_link name)
  sea_link_libraries(${name} sea_symex.ir sea_bounds.ir)
  sea_attach_bc(${name})
endfunction()

macro(sea_add_fuzz)
  if(SEA_ENABLE_FUZZ)
    sea_add_fuzz_executable(${ARGV})
  endif()
endmacro()

macro(sea_add_klee_bc name)
  cmake_parse_arguments(ARG
    "EXCLUDE_FROM_ALL" "" "" ${ARGN})

  set(TARGET_KLEE "${name}.klee")
  add_executable(${TARGET_KLEE} ${ARG_UNPARSED_ARGUMENTS})
  target_compile_definitions(${TARGET_KLEE} PUBLIC 
    MAX_INITIAL_SIZE=${MAX_INITIAL_SIZE}
    MAX_ITEM_SIZE=${MAX_ITEM_SIZE}
    MAX_INITIAL_ITEM_ALLOCATION=${MAX_INITIAL_ITEM_ALLOCATION}
    )
  klee_attach_bc_link(${TARGET_KLEE})
endmacro()

function(add_subset_test_target TEST_TARGET_NAME TEST_EXEC SET_NAME)

  # This adds the "make subset test" target.
  add_custom_target(${TEST_TARGET_NAME}
    COMMAND ${CMAKE_CTEST_COMMAND} -R ${TEST_EXEC}
    COMMENT "Running ${SET_NAME} unit tests.")
endfunction()

if(SEA_ENABLE_KLEE)
  add_subset_test_target("klee_test" "klee_" "klee")
  add_subset_test_target("sea_test" "unsat_test" "seahorn")
  # The next line of code sets up a subset of unit testing for new harness files (*.klee.c)
  # add_subset_test_target("sea_temp_test" "unsat_temp_" "temp seahorn")
endif()

function(sea_add_klee_test TARGET)
  sea_get_file_name(BC ${TARGET}.klee.ir)
  set(TIME_OUT_VAL 180) # Set a timeout value for 3 minutes
  add_test(NAME "klee_${TARGET}_test" COMMAND timeout ${TIME_OUT_VAL} klee --libc=uclibc --exit-on-error ${BC})
endfunction()

macro(sea_add_klee)
  if(SEA_ENABLE_KLEE)
    sea_add_klee_bc(${ARGV})
    sea_add_klee_test(${ARGV0})
  endif()
endmacro()

set(VERIFY_FLAGS $ENV{VERIFY_FLAGS} CACHE STRING "Flags for verify script")
separate_arguments(VERIFY_FLAGS)

function(sea_add_unsat_test TARGET)
  sea_get_file_name(BC ${TARGET}.ir)
  add_test(NAME "${TARGET}_unsat_test" COMMAND ${VERIFY_CMD} ${VERIFY_FLAGS} --expect=unsat ${BC})
endfunction()



# Set upper bound on data structures
set(MAX_LINKED_LIST_ITEM_ALLOCATION_SIZE 5)
set(MAX_BUFFER_SIZE 10)
set(MAX_STRING_LEN 16)
set(MAX_INITIAL_SIZE 10)
set(MAX_ITEM_SIZE 2)
set(MAX_INITIAL_ITEM_ALLOCATION 9223372036854775808ULL)

# Compile-time definitions
add_definitions(
  -DMAX_BUFFER_SIZE=${MAX_BUFFER_SIZE}
  -DMAX_STRING_LEN=${MAX_STRING_LEN}
  -DMAX_LINKED_LIST_ITEM_ALLOCATION_SIZE=${MAX_LINKED_LIST_ITEM_ALLOCATION_SIZE}
  )

configure_file(include/config.h.in ${PROJECT_BINARY_DIR}/include/config.h)
configure_file(sea.yaml sea.yaml @ONLY)
configure_file(sea_cex_base.yaml sea.cex.yaml @ONLY)
configure_file(sea_vac.yaml sea.vac.yaml @ONLY)

# compilation recipes for aws-c-common library
add_subdirectory(aws-c-common-stubs)

add_subdirectory(lib)

add_subdirectory(jobs/add_size_checked)
add_subdirectory(jobs/add_size_saturating)
add_subdirectory(jobs/mul_size_checked)
add_subdirectory(jobs/mul_size_saturating)
add_subdirectory(jobs/is_power_of_two)
add_subdirectory(jobs/round_up_to_power_of_two)

add_subdirectory(jobs/nospec_mask)

add_subdirectory(jobs/ptr_eq)

add_subdirectory(jobs/array_eq_c_str)
add_subdirectory(jobs/array_eq_c_str_ignore_case)
add_subdirectory(jobs/array_eq_ignore_case)
add_subdirectory(jobs/array_list_back)
add_subdirectory(jobs/array_list_capacity)
add_subdirectory(jobs/array_list_clean_up)
add_subdirectory(jobs/array_list_clear)
add_subdirectory(jobs/array_list_comparator_string)
add_subdirectory(jobs/array_list_copy)
add_subdirectory(jobs/array_list_ensure_capacity)
add_subdirectory(jobs/array_list_erase)
add_subdirectory(jobs/array_list_front)
add_subdirectory(jobs/array_list_get_at)
add_subdirectory(jobs/array_list_get_at_ptr)
add_subdirectory(jobs/array_list_init_dynamic)
add_subdirectory(jobs/array_list_init_static)
add_subdirectory(jobs/array_list_length)
add_subdirectory(jobs/array_list_pop_back)
add_subdirectory(jobs/array_list_pop_front)
add_subdirectory(jobs/array_list_pop_front_n)
add_subdirectory(jobs/array_list_push_back)
add_subdirectory(jobs/array_list_set_at)
add_subdirectory(jobs/array_list_shrink_to_fit)
add_subdirectory(jobs/array_list_sort)
add_subdirectory(jobs/array_list_swap)
add_subdirectory(jobs/array_list_swap_contents)
add_subdirectory(jobs/byte_buf_advance)
add_subdirectory(jobs/byte_buf_append)
add_subdirectory(jobs/byte_buf_append_dynamic)
add_subdirectory(jobs/byte_buf_append_with_lookup)
add_subdirectory(jobs/byte_buf_cat)
add_subdirectory(jobs/byte_buf_clean_up)
add_subdirectory(jobs/byte_buf_clean_up_secure)
add_subdirectory(jobs/byte_buf_eq)
add_subdirectory(jobs/byte_buf_eq_c_str)
add_subdirectory(jobs/byte_buf_eq_c_str_ignore_case)
add_subdirectory(jobs/byte_buf_eq_ignore_case)
add_subdirectory(jobs/byte_buf_from_array)
add_subdirectory(jobs/byte_buf_from_c_str)
add_subdirectory(jobs/byte_buf_from_empty_array)
add_subdirectory(jobs/byte_buf_init)
add_subdirectory(jobs/byte_buf_init_copy)
add_subdirectory(jobs/byte_buf_init_copy_from_cursor)
add_subdirectory(jobs/byte_buf_reserve)
add_subdirectory(jobs/byte_buf_reserve_relative)
add_subdirectory(jobs/byte_buf_reset)
add_subdirectory(jobs/byte_buf_secure_zero)
add_subdirectory(jobs/byte_buf_write)
add_subdirectory(jobs/byte_buf_write_be16)
add_subdirectory(jobs/byte_buf_write_be32)
add_subdirectory(jobs/byte_buf_write_be64)
add_subdirectory(jobs/byte_buf_write_from_whole_buffer)
add_subdirectory(jobs/byte_buf_write_from_whole_cursor)
add_subdirectory(jobs/byte_buf_write_from_whole_string)
add_subdirectory(jobs/byte_buf_write_u8)
add_subdirectory(jobs/byte_cursor_advance)
add_subdirectory(jobs/byte_cursor_advance_nospec)
add_subdirectory(jobs/byte_cursor_compare_lexical)
add_subdirectory(jobs/byte_cursor_compare_lookup)
add_subdirectory(jobs/byte_cursor_eq)
add_subdirectory(jobs/byte_cursor_eq_byte_buf)
add_subdirectory(jobs/byte_cursor_eq_byte_buf_ignore_case)
add_subdirectory(jobs/byte_cursor_eq_c_str)
add_subdirectory(jobs/byte_cursor_eq_c_str_ignore_case)
add_subdirectory(jobs/byte_cursor_eq_ignore_case)
add_subdirectory(jobs/byte_cursor_from_array)
add_subdirectory(jobs/byte_cursor_from_buf)
add_subdirectory(jobs/byte_cursor_from_c_str)
add_subdirectory(jobs/byte_cursor_from_string)
add_subdirectory(jobs/byte_cursor_left_trim_pred)
add_subdirectory(jobs/byte_cursor_read)
add_subdirectory(jobs/byte_cursor_read_and_fill_buffer)
add_subdirectory(jobs/byte_cursor_read_be16)
add_subdirectory(jobs/byte_cursor_read_be32)
add_subdirectory(jobs/byte_cursor_read_be64)
add_subdirectory(jobs/byte_cursor_read_u8)
add_subdirectory(jobs/byte_cursor_right_trim_pred)
add_subdirectory(jobs/linked_list_back)
add_subdirectory(jobs/linked_list_begin)
add_subdirectory(jobs/linked_list_end)
add_subdirectory(jobs/linked_list_front)
add_subdirectory(jobs/linked_list_init)
add_subdirectory(jobs/linked_list_remove)
add_subdirectory(jobs/linked_list_pop_back)
add_subdirectory(jobs/linked_list_pop_front)
add_subdirectory(jobs/linked_list_prev)
add_subdirectory(jobs/linked_list_next)
add_subdirectory(jobs/linked_list_node_reset)
add_subdirectory(jobs/linked_list_push_back)
add_subdirectory(jobs/linked_list_push_front)
add_subdirectory(jobs/linked_list_swap_contents)
add_subdirectory(jobs/linked_list_insert_after)
add_subdirectory(jobs/linked_list_insert_before)
add_subdirectory(jobs/linked_list_rbegin)
add_subdirectory(jobs/linked_list_rend)
add_subdirectory(jobs/string_bytes)
add_subdirectory(jobs/string_compare)
add_subdirectory(jobs/string_eq)
add_subdirectory(jobs/string_eq_byte_buf)
add_subdirectory(jobs/string_eq_byte_buf_ignore_case)
add_subdirectory(jobs/string_eq_byte_cursor)
add_subdirectory(jobs/string_eq_byte_cursor_ignore_case)
add_subdirectory(jobs/string_eq_c_str)
add_subdirectory(jobs/string_eq_c_str_ignore_case)
add_subdirectory(jobs/string_eq_ignore_case)
add_subdirectory(jobs/string_new_from_array)
add_subdirectory(jobs/string_new_from_c_str)
add_subdirectory(jobs/string_new_from_string)
#
add_subdirectory(jobs/priority_queue_size)
add_subdirectory(jobs/priority_queue_capacity)
add_subdirectory(jobs/priority_queue_top)
add_subdirectory(jobs/priority_queue_init_static)
add_subdirectory(jobs/priority_queue_init_dynamic)
add_subdirectory(jobs/priority_queue_clean_up)
add_subdirectory(jobs/ring_buffer_clean_up)

add_subdirectory(jobs/ring_buffer_init)
if(${SEA_WITH_BLEEDING_EDGE})
  add_subdirectory(jobs/priority_queue_s_swap)
  add_subdirectory(jobs/priority_queue_s_sift_up)
  add_subdirectory(jobs/priority_queue_s_sift_down)
  add_subdirectory(jobs/priority_queue_s_sift_either)
  add_subdirectory(jobs/priority_queue_s_remove_node)
  add_subdirectory(jobs/priority_queue_remove)
  add_subdirectory(jobs/priority_queue_pop)
  add_subdirectory(jobs/priority_queue_push)
  add_subdirectory(jobs/priority_queue_push_ref)

  add_subdirectory(jobs/ring_buffer_release)
  add_subdirectory(jobs/ring_buffer_acquire)
  add_subdirectory(jobs/ring_buffer_buf_belongs_to_pool)
  add_subdirectory(jobs/ring_buffer_acquire_up_to)
endif()

if(${SEA_ENABLE_BENCHMARK})
  add_subdirectory(benchmark_jobs/linked_list_pop_back_benchmark)
endif()

