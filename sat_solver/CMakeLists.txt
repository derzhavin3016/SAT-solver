# force c++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(sat)
target_sources(sat PUBLIC FILE_SET CXX_MODULES FILES sat.cppm)

add_executable(solver main.cc)
set_target_properties(solver PROPERTIES RUNTIME_OUTPUT_DIRECTORY
                                        "${PROJECT_BINARY_DIR}/bin/")

apply_compiler_flags(solver PRIVATE)
target_link_libraries(solver sat)

if(BUILD_TESTS)
  find_package(GTest REQUIRED)

  set(TESTS_FILES example.cc)

  foreach(TEST_FILE ${TESTS_FILES})
    set(TEST_NAME ${TEST_FILE}_test)
    add_executable(${TEST_NAME} ${TEST_FILE})
    target_link_libraries(${TEST_NAME} PRIVATE sat)
    target_link_libraries(${TEST_NAME} PRIVATE gtest_main gtest)
    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME} --gtest_color=yes)
  endforeach()

endif()
