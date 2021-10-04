cmake_minimum_required(VERSION 3.17)

project(dsj_utils)

set(CMAKE_CXX_STANDARD 17)

#add_subdirectory(tests)

#include_directories(/usr/local/include)
#link_directories(/usr/local/lib)

include_directories(external/curl/include)
link_directories(external/curl/lib)

add_library(dsj_utils
        cpp/easy_array.cpp
        header/easy_array.h
        cpp/easy_common.cpp
        header/easy_common.h
        cpp/easy_map.cpp
        header/easy_map.h
        cpp/easy_string.cpp
        header/easy_string.h
        cpp/easy_timer.cpp
        header/easy_timer.h
        cpp/easy_vector.cpp
        header/easy_vector.h
        header/macros.h
        cpp/Props.cpp
        header/Props.h
        cpp/random_string.cpp
        header/random_string.h
        cpp/TimeMetric.cpp
        header/TimeMetric.h
        cpp/Rest.cpp
        header/Rest.h
        )

add_executable(EasyArray tests/catch.hpp tests/EasyArray.cpp)
target_link_libraries(EasyArray PRIVATE dsj_utils)


add_executable(EasyMap tests/catch.hpp tests/EasyMapTest.cpp)
target_link_libraries(EasyMap PRIVATE dsj_utils)

add_executable(EasyString tests/catch.hpp tests/EasyStringTest.cpp)
target_link_libraries(EasyString PRIVATE dsj_utils)

add_executable(EasyTimer tests/catch.hpp tests/EasyTimerTest.cpp)
target_link_libraries(EasyTimer PRIVATE dsj_utils)

add_executable(EasyVector tests/catch.hpp tests/EasyVectorTest.cpp)
target_link_libraries(EasyVector PRIVATE dsj_utils)

add_executable(MetricTest tests/catch.hpp tests/MetricTest.cpp)
target_link_libraries(MetricTest PRIVATE dsj_utils)

add_executable(RandomString tests/catch.hpp tests/RandomStringTest.cpp)
target_link_libraries(RandomString PRIVATE dsj_utils)


add_executable(RestTest tests/catch.hpp tests/RestTest.cpp)
target_link_libraries(RestTest PRIVATE dsj_utils)
target_link_libraries(RestTest PRIVATE curl)