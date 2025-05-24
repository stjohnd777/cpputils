project(tests_string)

file(GLOB TEST_SOURCES "*.cpp")

find_package(Catch2 REQUIRED)

add_executable(dsj_timer_strings ${TEST_SOURCES})

target_link_libraries(dsj_timer_strings PRIVATE dsj_string Catch2::Catch2WithMain)

target_include_directories(dsj_timer_strings PRIVATE ${CMAKE_SOURCE_DIR}/header)

# Optionally enable CTest
enable_testing()
add_test(NAME dsj_timer_strings COMMAND dsj_timer_strings)
