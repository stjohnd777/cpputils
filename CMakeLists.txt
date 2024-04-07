cmake_minimum_required(VERSION 3.17)
project(dsj_utils)

set(CMAKE_CXX_STANDARD 17)
add_subdirectory(src/tests)
include_directories(src/header)



find_package(CURL REQUIRED)
find_package(Boost REQUIRED  )

add_library(dsj_utils
        src/header/macros.h
        src/header/props.h
        src/header/easy_common.h
        src/header/easy_string.h
        src/header/easy_array.h
        src/header/easy_vector.h
        src/header/easy_map.h
        src/header/time_metrics.h
        src/header/random_string.h
        src/header/easy_timer.h
src/cpp/easy_string.cpp
src/cpp/easy_timer.cpp
src/cpp/random_string.cpp
src/cpp/time_metrics.cpp
        )
target_link_directories( dsj_utils  PRIVATE ${Boost_LIBRARIES} )



install(TARGETS dsj_utils ARCHIVE DESTINATION lib)
install(DIRECTORY src/ DESTINATION include FILES_MATCHING PATTERN "*.h")
install(FILES dsj_utilsConfig.cmake DESTINATION lib/cmake/dsj_utils)

