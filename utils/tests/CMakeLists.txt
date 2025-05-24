project(tests_utils)

file(GLOB TEST_SOURCES "*.cpp")

find_package(Catch2 REQUIRED)

add_executable(dsj_utils_tests ${TEST_SOURCES})

target_link_libraries(dsj_utils_tests PRIVATE dsj_utils Catch2::Catch2WithMain)

target_include_directories(dsj_utils_tests PRIVATE ${CMAKE_SOURCE_DIR}/header)

# Optionally enable CTest
enable_testing()
add_test(NAME dsj_utils_tests COMMAND dsj_utils_tests)
