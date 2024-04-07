project(tests)



include_directories(../header)

# Add Catch2
include(FetchContent)
FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v3.5.3  # Use the version you prefer
)
FetchContent_MakeAvailable(Catch2)

# Enable CTest (optional but recommended)
include(CTest)
enable_testing()

add_executable(EasyArray tests/ test_easy_array.cpp)
target_link_libraries(EasyArray PRIVATE dsj_utils  Catch2::Catch2)

add_executable(EasyMap test_easy_map.cpp)
target_link_libraries(EasyMap PRIVATE dsj_utils Catch2::Catch2)

add_executable(EasyString test_easy_string.cpp)
target_link_libraries(EasyString PRIVATE dsj_utils Catch2::Catch2)

add_executable(EasyTimer test_easy_timer.cpp)
target_link_libraries(EasyTimer PRIVATE dsj_utils Catch2::Catch2)

add_executable(EasyVector test_easy_vector.cpp)
target_link_libraries(EasyVector PRIVATE dsj_utils Catch2::Catch2)

add_executable(MetricTest test_metric_test.cpp)
target_link_libraries(MetricTest PRIVATE dsj_utils Catch2::Catch2)

add_executable(RandomString test_random_string.cpp)
target_link_libraries(RandomString PRIVATE dsj_utils Catch2::Catch2)

