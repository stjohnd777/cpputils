#include <iostream>
#include <functional>
#include <chrono>

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../header/easy_timer.h"

using namespace std;
using namespace dsj;
using namespace std::chrono_literals;

TEST_CASE( "easy_timer 0", "[SetTimeout]") {
    
    using namespace std;
    using namespace dsj;
    std::function<bool()> f = [&] (void) ->bool {
        cout << "Alarm Fired" << endl;
        return true;
    };
 
    auto spHandle = SetTimeout (f, 1000,true);
    
    using namespace std::chrono_literals;
    std::cout << "Hello waiter\n" << std::flush;
    auto start = std::chrono::high_resolution_clock::now();
    std::this_thread::sleep_for(2000ms);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed = end-start;
    std::cout << "Waited " << elapsed.count() << " ms\n";
}



TEST_CASE( "easy_timer 1", "[SetTimeout]") {

    using namespace std;
    using namespace dsj;
    std::function<bool()> f = [&] (void) ->bool {
        cout << "Alarm Fired" << endl;
        return true;
    };

    using namespace std::chrono_literals;
    auto start = std::chrono::high_resolution_clock::now();

    auto handle = SetTimeout (f, 1000,true);
    if (handle->theThread->joinable()){
        handle->theThread->join();
    }

    while ( handle->state != TimerHandle::COMPLETED){
        REQUIRE(handle->state == TimerHandle::INIT);
    }
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> elapsed = end-start;
    std::cout << "Waited " << elapsed.count() << " ms\n";

    REQUIRE(handle->state == TimerHandle::COMPLETED);
    REQUIRE(elapsed.count() >= 1000);

}


TEST_CASE( "easy_timer 2", "[SetTimeout]") {
    using namespace std;
    using namespace dsj;
    std::function<bool()> f = [&] (void) ->bool {
        cout << "Alarm Fired" << endl;
        return true;
    };

    auto handle = SetTimeout (f, 1000,false);

    using namespace std::chrono_literals;
    std::this_thread::sleep_for(2000ms);
    REQUIRE(handle->state == TimerHandle::COMPLETED);
}


TEST_CASE( "easy_timer 3", "[SetInterval,join]") {

    auto handle = SetInterval([&]()->void {
        static int count = 1;
        cout << "Fired Interval " << count << endl;
        count ++;
    },1000,false);
    handle->executeLimit = 10;

    handle->join();
    REQUIRE(handle->executedCount == 10);

}


TEST_CASE( "easy_timer 4", "[SetInterval,detached]") {

    auto handle = SetInterval([&]()->void {
        static int count = 1;
        cout << "Fired Interval " << count << endl;
        count ++;
    },1000,true);
    handle->executeLimit = 10;

    while ( handle->state != TimerHandle::COMPLETED){
    }

    REQUIRE(handle->executedCount == 10);

}


TEST_CASE( "easy_timer 5", "[SetInterval,joinable]"){

    auto start = std::chrono::high_resolution_clock::now();

    int intervalTime = 1000;
    bool isDetached = true;
    int  maxExecuctions = 10;
    std::shared_ptr<TimerHandle> handle = SetInterval([&]()->void {
        static int counter = 1;
        cout << "Fired Interval " << counter <<  endl;
        counter ++;
    },intervalTime,isDetached);//,maxExecuctions);
    handle->executeLimit = 10;
    if ( handle->theThread->joinable()){
        handle->join();
    }
    else {
        while ( handle->state != TimerHandle::COMPLETED){
            //XCTAssert(handle->state == TimerHandle::RUNNING || handle->state == TimerHandle::SLEEPING);
        }
    }
    REQUIRE(handle->executedCount == maxExecuctions);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed = end-start;
    REQUIRE(elapsed.count() >= 1000 * maxExecuctions);
}


TEST_CASE( "easy_timer 6", "[SetIntervals,REQUEST_CANCEL]"){

    auto main = SetInterval([&]()->void {
        static int count = 1;
        cout << "main ==>" << count << endl;
        count ++;
    },10,false);
    main->executeLimit = 1000;


    auto handle1 = SetInterval([&]()->void {
        static int count = 1;
        cout << "Fired Interval 1 1000ms " << count << endl;
        count ++;
    },1000,false);


    auto handle2 = SetInterval([&]()->void {
        static int count = 1;
        cout << "Fired Interval 2 1000ms" << count << endl;
        count ++;
    },300,false);

    auto handle3 = SetInterval([&]()->void {
        static int count = 1;
        cout << "Fired Interval 3 1000ms" << count << endl;
        count ++;
    },500,false);

    main->join();


    handle1->state = dsj::TimerHandle::REQUEST_CANCEL;
    handle1->join();
    handle2->state = dsj::TimerHandle::REQUEST_CANCEL;
    handle2->join();
    handle3->state = dsj::TimerHandle::REQUEST_CANCEL;
    handle3->join();

    cout << "EXIT" << endl;

//    int pollRate = 1000;
//    bool isRuning = true;
//    while (isRuning)
//    {
//        std::this_thread::sleep_for(std::chrono::milliseconds(pollRate));
//
//    }
}


