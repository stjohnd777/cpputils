
#define CATCH_CONFIG_MAIN

#include "catch.hpp"

#include <string>
#include <iostream>
#include <chrono>
#include <thread>

using namespace std;

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
    endpoint->get("http://www.google.com",[](string in){
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
        cout << "handler done" << endl;
    }
}

TEST_CASE( "Rest asynchronous repeat x 3 uuid", "[uuid]") {
    cout << "RestTest Start" << endl;

    int counter = 0;
    auto endpoint =  new RestClient();

    endpoint->get("http://localhost:8989/uuid", [&](string in) {
        counter++;
        cout << in << endl;
        cout << "handler done" << endl;
    });

    endpoint->get("http://localhost:8989/uuid", [&](string in) {
        counter++;
        cout << in << endl;
        cout << "handler done" << endl;
    });
    endpoint->get("http://localhost:8989/uuid", [&](string in) {
        counter++;
        cout << in << endl;
        cout << "handler done" << endl;
    });
    std::this_thread::sleep_for(3000ms);
    REQUIRE( counter == 3);

}


TEST_CASE( "RestTest5", "[uuid]") {
    cout << "RestTest Start" << endl;
    for (int i=0;i<10;i++) {
        auto endpoint =  new RestClient();
        endpoint->get("http://localhost:8989/uuid", [&](string in) {
            cout << in << endl;
            cout << "handler done" << endl;
        });
        std::this_thread::sleep_for(2000ms);
    }
}

TEST_CASE( "RestTest6", "[uuid]") {
    cout << "RestTest Start" << endl;
    int count_down = 10;

    auto  wrapper = [&] () -> void {
        auto endpoint =  new RestClient();
        endpoint->get("http://localhost:8989/uuid", [&](string in) {
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
}