set(CMAKE_EXPERIMENTAL_CXX_MODULE_DYNDEP 1)

if(CMAKE_MINOR_VERSION STREQUAL "26")
  set(CMAKE_EXPERIMENTAL_CXX_MODULE_CMAKE_API
      "2182bf5c-ef0d-489a-91da-49dbc3090d2a")
elseif(CMAKE_MINOR_VERSION STREQUAL "3.25")
  set(CMAKE_EXPERIMENTAL_CXX_MODULE_CMAKE_API
      "3c375311-a3c9-4396-a187-3227ef642046")
else()
  message(FATAL_ERROR "Only cmake 3.26 or 3.25 are supported")
endif()

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_EXTENSIONS OFF)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  message(FATAL_ERROR "Only Clang is supported")
  # include(gcc_support.cmake)
endif()

add_compile_options(--stdlib=libc++ -fmodules)
add_link_options(--stdlib=libc++)
