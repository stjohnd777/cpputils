
#define CATCH_CONFIG_MAIN

#include "catch.hpp"

#include <string>
#include <iostream>
#include <chrono>
#include <thread>



using namespace std;

#include "../../external/nlohmann-json/json.h"
#include "../header/Rest.h"

using namespace dsj;
using namespace std::chrono_literals;

TEST_CASE( "Rest synchronous once google", "[get]") {

    auto endpoint =  new RestClient();
    cout << "RestTest Start" << endl;
    auto data = endpoint->get("http://www.google.com");
    cout << data << endl;
    delete endpoint;
    cout << "RestTest End" << endl;
}

TEST_CASE( "Rest asynchronous once google", "[getAsync]") {

    auto endpoint =  new RestClient();
    cout << "RestTest Start" << endl;
    endpoint->getAsync("http://www.google.com", [](string in) {
        cout << in << endl;
    });
    std::this_thread::sleep_for(2000ms);

}


TEST_CASE( "Rest asynchronous once uuid", "[uuid]") {
    cout << "RestTest Start" << endl;
    for (int i=0;i<10;i++) {
        auto endpoint =  new RestClient();
        auto data = endpoint->get("http://localhost:8989/uuid");
        cout << data << endl;
        cout << "handler done" << endl;
    }
}

TEST_CASE( "Rest synchronous repeat x 10 uuid", "[uuid]") {
    cout << "RestTest Start" << endl;
    auto endpoint =  new RestClient();
    for (int i=0;i<10;i++) {
        auto data = endpoint->get("http://localhost:8989/uuid");
        cout << data << endl;
        nlohmann::json j =  nlohmann::json::parse(data);
        auto uuid = j["uuid"];
        auto success = j["success"];
        cout << uuid << ":" << success <<  endl;
        cout << "handler done" << endl;
    }
}

TEST_CASE( "Rest asynchronous repeat x 10 uuid", "[uuid]") {
    cout << "RestTest Start" << endl;

    int counter = 0;
    auto endpoint =  new RestClient();

    for (int i=0;i<10;i++) {
        endpoint->getAsync("http://localhost:8989/uuid", [&](string in) {
            counter++;
            cout << in << endl;
            cout << "handler done" << endl;
        });
    }

    std::this_thread::sleep_for(3000ms);
    REQUIRE( counter == 10);

}


TEST_CASE( "RestTest async in separate threads threads", "[uuid]") {
    cout << "RestTest Start" << endl;
    int count_down = 10;

    auto  wrapper = [&] () -> void {
        auto endpoint =  new RestClient();
        endpoint->getAsync("http://localhost:8989/uuid", [&](string in) {
            cout << in << endl;
            cout << "handler done" << endl;
            std::mutex m_mutex;
            std::lock_guard<std::mutex> guard(m_mutex);
            count_down--;
        });
    };

    for (int i=0;i<10;i++) {
        thread t( wrapper);
        t.detach();
    }

    while ( count_down >0) {
        std::this_thread::sleep_for(1000ms);
    }
    REQUIRE(count_down ==0);
}

TEST_CASE("make json", "[ok]") {

    using namespace nlohmann;

    json j2 = {
            {"time", 999},
            {"lat", 3.141},
            {"long", 232},
            {"alt", 333},
            {"angle", 333}
    };

    cout << j2 << endl;

    string s = j2.dump();
    cout << s << endl;
}