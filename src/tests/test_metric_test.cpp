#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <iostream>
#include <string>

#include "../header/time_metrics.h"

using namespace std;
using namespace dsj::utils;

TEST_CASE( "Metric Hello World", "[Hello World]") {
    TimeMetrics::Start("M001");
    for( unsigned long i =1; i< 1000 ; i++){
        std::cout << i << std::endl;
    }
    TimeMetrics::Stop("M001");
    cout << TimeMetrics::Average("M001");
}

