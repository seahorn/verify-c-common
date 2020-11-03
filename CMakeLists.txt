cmake_minimum_required(VERSION 3.18.4)
project(verify-c-common C CXX)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/llvmir)
include(LLVMIRUtil)

enable_testing()


option(SEA_ENABLE_FUZZ "Enable fuzzing" OFF)

if (CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR )
  message (FATAL_ERROR
    "In-source builds are not allowed. Please clean your source tree and try again.")
endif()

# Default is release with debug info
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING
    "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel." FORCE)
endif()

set(SEAHORN_ROOT "/usr" CACHE PATH "Path to SeaHorn installation")
set(SEA_LINK "llvm-link" CACHE STRING "Path to llvm-link")
set(LLVMIR_LINK ${SEA_LINK})
set(SEA_OPT "${SEAHORN_ROOT}/bin/seaopt" CACHE STRING  "Path to seaopt binary")
set(LLVMIR_OPT ${SEA_OPT})

set(AWS_C_COMMON_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/aws-c-common)

if (SEA_ENABLE_FUZZ)
  add_subdirectory(${AWS_C_COMMON_ROOT})
endif()

set(SEA_LIB ${CMAKE_CURRENT_SOURCE_DIR}/seahorn/lib)

configure_file(verify.py.in verify @ONLY)
set(VERIFY_SCRIPT ${CMAKE_CURRENT_BINARY_DIR}/verify-c-common.sh)
set(VERIFY_CMD ${CMAKE_CURRENT_BINARY_DIR}/verify)

include_directories(seahorn/include)
include_directories(aws-c-common/include)
#include_directories(aws-c-common/build/generated/include)
include_directories(${SEAHORN_ROOT}/include)
add_subdirectory(seahorn)

