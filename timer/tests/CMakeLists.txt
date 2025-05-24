project(tests_timer)

file(GLOB TEST_SOURCES "*.cpp")

find_package(Catch2 REQUIRED)

add_executable(dsj_timer_tests ${TEST_SOURCES})

target_link_libraries(dsj_timer_tests PRIVATE dsj_timer Catch2::Catch2WithMain)

target_include_directories(dsj_timer_tests PRIVATE ${CMAKE_SOURCE_DIR}/header)

# Optionally enable CTest
enable_testing()
add_test(NAME dsj_timer_tests COMMAND dsj_timer_tests)
