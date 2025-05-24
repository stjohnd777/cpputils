cmake_minimum_required(VERSION 4.0.2)
set(CMAKE_CXX_STANDARD 17)
project(dsj_timer)

# Use file(GLOB ...) to collect all .h and .cpp files
file(GLOB DSJ_TIMER_HEADERS "header/*.h")
file(GLOB DSJ_TIMER_SOURCES "cpp/*.cpp")

add_library(dsj_timer
        ${DSJ_TIMER_HEADERS}
        ${DSJ_TIMER_SOURCES}
)
target_include_directories(dsj_timer PUBLIC header)


install(TARGETS dsj_timer ARCHIVE DESTINATION lib)
install(DIRECTORY header/ DESTINATION include FILES_MATCHING PATTERN "*.h")
install(FILES dsj_timerConfig.cmake DESTINATION lib/cmake/dsj_timer)

add_subdirectory(tests)