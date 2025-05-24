project(tests)

file(GLOB TEST_SOURCES "*.cpp")

find_package(Catch2 REQUIRED)

add_executable(dsj_containers_tests ${TEST_SOURCES})

target_link_libraries(dsj_containers_tests PRIVATE dsj_containers Catch2::Catch2WithMain)

target_include_directories(dsj_containers_tests PRIVATE ${CMAKE_SOURCE_DIR}/header)

# Optionally enable CTest
enable_testing()
add_test(NAME dsj_containers_tests COMMAND dsj_containers_tests)
