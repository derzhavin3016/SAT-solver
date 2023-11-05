cmake_minimum_required(VERSION 3.28 FATAL_ERROR)

if("${CMAKE_BINARY_DIR}" STREQUAL "${CMAKE_SOURCE_DIR}")
  message(
    FATAL_ERROR
      "In-source builds are disabled.
  Please create a subfolder and use `cmake ..` inside it.
  NOTE: cmake will now create CMakeCache.txt and CMakeFiles/*.
  You must delete them, or cmake will refuse to work.")
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Release")
  string(APPEND CMAKE_CXX_FLAGS_RELEASE " -O2")
endif()

macro(check_compiler_version COMPILER VER)
  if(CMAKE_CXX_COMPILER_ID STREQUAL ${COMPILER})
    if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS ${VER})
      message(
        FATAL_ERROR
          "Insufficient ${COMPILER} version. Needed: ${VER}. Your: ${CMAKE_CXX_COMPILER_VERSION}"
      )
    endif()
  endif()
endmacro()

check_compiler_version("Clang" "17.0.0")

project(sat-solver LANGUAGES CXX)

include(cmake/list_dirs.cmake)
include(cmake/upd_tar_list.cmake)
include(cmake/comp_flags.cmake)
include(cmake/clang_format.cmake)

# indicate the tests build
option(BUILD_TESTS "Build tests" OFF)
# add -Werror option
option(ENABLE_WERROR "Enable -Werror option (CI)" OFF)

if(BUILD_TESTS)
  enable_testing()
endif()


add_subdirectory(sat_solver)
