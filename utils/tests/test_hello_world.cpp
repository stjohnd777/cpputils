#include <catch2/catch_test_macros.hpp>
#include <iostream>

TEST_CASE("Hello World") {
    std::cout << "Hello, World!" << std::endl;
    REQUIRE(1 == 1);
}