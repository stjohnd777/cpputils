 
 #include <catch2/catch_test_macros.hpp>
#include "random_string.h"

#include <iostream>
#include <string>
#include <sstream>

using namespace std;
using namespace dsj::utils;



TEST_CASE( "Random I", "[II]") {

}

TEST_CASE( "Random II", "[II]") {

}

TEST_CASE( "Random III", "[II]") {
    string i = dsj::utils::random_int(100);
    cout << i << endl;
    REQUIRE(i.length() == 100);

    i = dsj::utils::random_int(10000000);
    cout << i << endl;
    REQUIRE(i.length() == 10000000);
}
