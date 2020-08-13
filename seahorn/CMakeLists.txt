function(sea_attach_bc)
  set(SOURCE_EXE ${ARGV0})
  set(TARGET_BC "${SOURCE_EXE}.ir")
  set(TARGET_OBJ "${SOURCE_EXE}.obj")

  set_target_properties(${SOURCE_EXE} PROPERTIES LINKER_LANGUAGE C)
  target_compile_options(${SOURCE_EXE} PUBLIC -O1 -Xclang -disable-llvm-optzns )
  target_compile_options(${SOURCE_EXE} PUBLIC -Wno-macro-redefined)
  set_property(TARGET ${SOURCE_EXE} PROPERTY EXCLUDE_FROM_ALL ON)

  llvmir_attach_bc_target(TARGET ${TARGET_OBJ} DEPENDS ${SOURCE_EXE})
  set_property(TARGET ${TARGET_OBJ} PROPERTY EXCLUDE_FROM_ALL ON)
  llvmir_attach_link_target(TARGET ${TARGET_BC} DEPENDS ${TARGET_OBJ})
  add_dependencies(${TARGET_BC} ${TARGET_OBJ})
  set_property(TARGET ${TARGET_BC} PROPERTY EXCLUDE_FROM_ALL OFF)
endfunction()

add_definitions(-D__SEAHORN__)
add_subdirectory(jobs/array_eq_c_str)

configure_file(sea.yaml sea.yaml @ONLY)
configure_file(get_job_options.py get_job_options.py)
