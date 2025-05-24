cmake_minimum_required(VERSION 4.0.2)
set(CMAKE_CXX_STANDARD 17)
project(dsj_utils)

# Use file(GLOB ...) to collect all .h and .cpp files
file(GLOB DSJ_UTILS_HEADERS "header/*.h")
file(GLOB DSJ_UTILS_SOURCES "cpp/*.cpp")

add_library(dsj_utils
        ${DSJ_UTILS_HEADERS}
        ${DSJ_UTILS_SOURCES}
)
target_include_directories(dsj_utils PUBLIC header)


install(TARGETS dsj_utils ARCHIVE DESTINATION lib)
install(DIRECTORY header/ DESTINATION include FILES_MATCHING PATTERN "*.h")
install(FILES dsj_utilsConfig.cmake DESTINATION lib/cmake/dsj_utils)

add_subdirectory(tests)