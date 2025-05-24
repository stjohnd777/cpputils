cmake_minimum_required(VERSION 4.0.2)
set(CMAKE_CXX_STANDARD 17)
project(dsj_string)

# Use file(GLOB ...) to collect all .h and .cpp files
file(GLOB DSJ_STRING_HEADERS "header/*.h")
file(GLOB DSJ_STRING_SOURCES "cpp/*.cpp")

add_library(dsj_string
        ${DSJ_STRING_HEADERS}
        ${DSJ_STRING_SOURCES}
)
target_include_directories(dsj_string PUBLIC header)


install(TARGETS dsj_string ARCHIVE DESTINATION lib)
install(DIRECTORY header/ DESTINATION include FILES_MATCHING PATTERN "*.h")
install(FILES dsj_stringConfig.cmake DESTINATION lib/cmake/dsj_string)

add_subdirectory(tests)