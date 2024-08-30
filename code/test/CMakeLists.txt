include(FetchContent)
include(CMakePrintHelpers)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()
include(GoogleTest)

file(GLOB_RECURSE test_sources RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *_test.cpp)

foreach(test_source ${test_sources})
  cmake_path(GET test_source FILENAME test_filename)
  string(REGEX REPLACE \.cpp "" test_targetname ${test_filename})

  # cmake_print_variables(test_source test_filename test_targetname)

  add_executable(
    ${test_targetname}
    ${test_source}
  )

  # cmake_print_variables(PROJECT_SOURCE_DIR)

  target_include_directories(${test_targetname} PUBLIC ${PROJECT_SOURCE_DIR})

  target_link_libraries(
    ${test_targetname}
    GTest::gtest_main
  )

  gtest_discover_tests(${test_targetname})
endforeach()

