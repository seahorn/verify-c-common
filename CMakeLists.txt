cmake_minimum_required(VERSION 3.18.4)
project(verify-c-common C CXX)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/llvmir)
include(LLVMIRUtil)
include(CTest)

enable_testing()

# Enables LLVM builtin functions for memory operations. We do not check these for memory safety.
# To check for memory safety, set this option to OFF. Then our wrappers will be used instead that
# check for memory safety and call builtin functions directly.
option(SEA_LLVM_MEM_BUILTINS "Use LLVM builtins memcpy/memmove without memory safety checks" OFF)


option(SEA_ENABLE_FUZZ "Enable fuzzing" OFF)
option(SEA_WITH_BLEEDING_EDGE "Enable bleeding edge proofs" OFF)

option(SEA_ENABLE_KLEE "Enable klee" OFF)
option(SEA_ENABLE_SMACK "Enable SMACK" OFF)
option(SEA_ENABLE_SYMBIOTIC "Enable symbiotic" OFF)

option(SEA_ALLOCATOR_CAN_FAIL "Use can fail allocator" OFF)

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
  message(
    FATAL_ERROR
    "In-source builds are not allowed. Please clean your source tree and try again."
  )
endif()

# Default is release with debug info
if(NOT CMAKE_BUILD_TYPE)
  set(
    CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING
    "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel." FORCE
  )
endif()

if(SEA_ENABLE_SMACK)
  set(SMACK_INCLUDE_DIR "/usr/local/share/smack/include" CACHE PATH "Path to SMACK include")
  set(LLVM_DIS "llvm-dis-10" CACHE STRING "Binary for llvm-dis")
  set(SMACK_ENCODING "unbounded-integer" CACHE STRING "Option for ineger / pointer encoding")
  set(SMACK_PROPERTY_CHECK "assertions" CACHE STRING "Option for SMACK property checks")
  option(SMACK_ENABLE_NO_MEM_SPLIT "Enable no memory splitting" OFF)
  set(SMACK_NO_MEM_SPLIT_OPT "--no-memory-splitting" CACHE STRING "Option for no memory splitting")
  if(NOT SMACK_ENABLE_NO_MEM_SPLIT)
    set(SMACK_NO_MEM_SPLIT_OPT "")
  endif()
endif()

set(SEAHORN_ROOT "/usr" CACHE PATH "Path to SeaHorn installation")
set(SEA_LINK "llvm-link" CACHE STRING "Path to llvm-link")
set(LLVMIR_LINK ${SEA_LINK})
set(SEA_OPT "${SEAHORN_ROOT}/bin/seaopt" CACHE STRING "Path to seaopt binary")
set(SEA_PP "${SEAHORN_ROOT}/bin/seapp" CACHE STRING "Path to seapp binary")
set(LLVMIR_OPT ${SEA_OPT})

set(AWS_C_COMMON_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/aws-c-common)

if(SEA_ENABLE_FUZZ)
  find_package(aws-c-common REQUIRED)
endif()

set(SEA_LIB ${CMAKE_CURRENT_SOURCE_DIR}/seahorn/lib)

configure_file(verify.py.in verify @ONLY)
set(VERIFY_SCRIPT ${CMAKE_CURRENT_BINARY_DIR}/verify-c-common.sh)
set(VERIFY_CMD ${CMAKE_CURRENT_BINARY_DIR}/verify)


# add the include directory from the build tree
include_directories(BEFORE ${CMAKE_CURRENT_BINARY_DIR}/include)

include_directories(seahorn/include)
include_directories(aws-c-common/include)
include_directories(${SEAHORN_ROOT}/include)
add_subdirectory(seahorn)
