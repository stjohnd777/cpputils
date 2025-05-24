cmake_minimum_required(VERSION 4.0.2)
set(CMAKE_CXX_STANDARD 17)
project(dsj_container)

# Use file(GLOB ...) to collect all .h and .cpp files
file(GLOB DSJ_CONTAINERS_HEADERS "header/*.h")
file(GLOB DSJ_CONTAINERS_SOURCES "cpp/*.cpp")
message(STATUS "Headers: ${DSJ_CONTAINERS_HEADERS}")
message(STATUS "Sources: ${DSJ_CONTAINERS_SOURCES}")

add_library(dsj_containers
    ${DSJ_CONTAINERS_HEADERS}
    ${DSJ_CONTAINERS_SOURCES}
)
target_include_directories(dsj_containers PUBLIC header)


install(TARGETS dsj_containers ARCHIVE DESTINATION lib)
install(DIRECTORY header/ DESTINATION include FILES_MATCHING PATTERN "*.h")
install(FILES dsj_containersConfig.cmake DESTINATION lib/cmake/dsj_containers)

add_subdirectory(tests)