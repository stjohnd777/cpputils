 
#include <catch2/catch_test_macros.hpp>

#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <array>
#include <random>

#include "easy_array.h"


using namespace std;
using dsj::easy_array;
using dsj::easy_vector;

TEST_CASE("std::for_each" ) {
    easy_array<int, 10> container;
    for (int i = 0; i < 10; i++) {
        container[i] = i;
    }

    REQUIRE(container.size() == 10);
    int index = 0;
    std::for_each(begin(container), end(container), [&](int i) {
        REQUIRE(i == index);
        index++;
    });
}

 
TEST_CASE("container.forEach" ) {
    easy_array<int, 10> container;
    for (int i = 0; i < 10; i++) {
        container[i] = i;
    }
    REQUIRE(container.size() == 10);
    int index = 0;
    container.forEach([&](int i) {
        REQUIRE(i == index);
        index++;
    });
}
 
TEST_CASE("size" ) {
    easy_array<int,100> container;
    for ( int i =0 ; i < 100; i++){
        container[i]=i % 10;
    }
    REQUIRE( container.size() == 100);
    auto ucontainer = container.unique();
    REQUIRE( ucontainer.size() == 10);
}

 
TEST_CASE("container.filter" ) {

    easy_array<int, 10> container;
    for (int i = 0; i < 10; i++) {
        container[i] = i;
    }
    REQUIRE( container.size() == 10);
    auto fcontainer = container.filter([&](int i){
        return i %2 ==0;
    });
    // [0,2,4,6,8]
    REQUIRE( fcontainer.size() == 5);
    int index = 0;
    fcontainer.forEach([&](int i){
        REQUIRE( i%2 == 0);
    });

    auto ofcontainer = container.filter([&](int i){
        return i %2 !=0;
    });
    ofcontainer.forEach([](int i){
        REQUIRE( i%2 != 0);
    });
}


TEST_CASE("container.map" ) {
    easy_array<int, 10> container;
    for (int i = 0; i < 10; i++) {
        container[i] = i;
    }

    REQUIRE(container.size() == 10);
    auto mapped = container.map<double>([](int i) {
        return M_PI * i * i;
    });

    int index = 0;
    REQUIRE(mapped.size() == 10);
    mapped.forEach([&](double area) {
        REQUIRE(area == index * index * M_PI);
        index++;
    });
}

 
TEST_CASE("container.shuffel" ) {
    easy_array<int, 10> container;
    for (int i = 0; i < 10; i++) {
        container[i] = i;
    }

    REQUIRE(container.size() == 10);
    container.shuffle();
    REQUIRE (container[6] != 5);
    std::cout << container.toString() << std::endl;
}

 
TEST_CASE("container.sort" ) {

    const std::string base10 = "0123456789";
    const std::string dictonary = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const std::string dictonary2 = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()?.,><:;~|}]{[";

    auto random_string= [&](std::string::size_type length) {
    auto dictonary_length = dictonary.length() - 1;
    std::string random_string;
    random_string.reserve(length);
    for (unsigned int i = 0; i < length; i++) {
        int aRandomInt = rand();
        unsigned int random_index = aRandomInt % dictonary_length;
        random_string += dictonary.at(random_index);
    }
    return random_string;
    };


    easy_array<std::string, 100> container;
    for (auto i = 0; i < 100; i++) {
        container[i] = random_string(40);
    }
    container.sort();

    std::string last = "";
    container.forEach([&](std::string s) {
        if (last != "") {
            REQUIRE(last < s);
        }
    });
}


TEST_CASE("container.sort([](..." ) {
    easy_array<int, 10> container;
    for (int i = 0; i < 10; i++) {
        container[i] = i;
    }

    REQUIRE(container.size() == 10);

    container.sort([&](int a, int b) {
                       // a < b
                       if (a % 2 == 0 && b % 2 != 0) {
                           return true;
                       } else if (b % 2 == 0 && a % 2 != 0) {
                           return false;
                       } else {
                           return a < b;
                       }
                   }
    );
    std::cout << container.toString() << std::endl;
    REQUIRE(container[0] == 0);
    REQUIRE(container[1] == 2);
    REQUIRE(container[2] == 4);
    REQUIRE(container[3] == 6);
    REQUIRE(container[4] == 8);

    REQUIRE(container[5] == 1);
    REQUIRE(container[6] == 3);
}

 

TEST_CASE("container.indexOf" ) {
    easy_array<int, 10> container;
    for (int i = 0; i < 10; i++) {
        container[i] = i;
    }

    REQUIRE(container.size() == 10);
    for (int i = 0; i < 10; i++) {
        REQUIRE (container.indexOf(i) == i);
    }
    REQUIRE (container.indexOf(5) == 5);
}


// TEST_CASE("testRemoveFirstOccurrenceOfItem","[0]" ) {

    
//     easy_array<int, 10> container;
//     for (int i = 0; i < 10; i++) {
//         container[i] = i;
//     }

//     REQUIRE( container.size() == 10);

//     for ( int i =0 ; i < 10; i++){
//         container.push_back(i);
//     }
//     // [0 1 2 3 4 5 6 7 8 9 ]
//     auto didRemove = container.removeFirstOccurrenceOfItem(0);
//     // [1 2 3 4 5 6 7 8 9 ]
//     REQUIRE ( didRemove == true);
//     int index = container.indexOf (0);
//     REQUIRE( index ==-1);

//     REQUIRE( container[0] == 1);
//     REQUIRE(  container.size() == 9);

//     didRemove = container.removeFirstOccurrenceOfItem(5);
//     REQUIRE ( didRemove == true);
//     // [1 2 3 4 6 7 8 9 ]
//     REQUIRE(  container.size() == 8);
//     REQUIRE( container[4] == 6);

//     didRemove = container.removeFirstOccurrenceOfItem(12);
//     REQUIRE ( didRemove == false);
// }



TEST_CASE("testRemoveLastOccurrenceOfItem" ) {
    
    easy_vector<int> easyVector;
    for ( int i =0 ; i < 30; i++){
        easyVector.push_back(i % 10);
    }
    REQUIRE(easyVector.size() == 30);

    auto didRemove = easyVector.removeLastOccurrenceOfItem(5);
    REQUIRE ( didRemove == true);
    REQUIRE(easyVector.size() == 29);

    didRemove = easyVector.removeLastOccurrenceOfItem(5);
    REQUIRE ( didRemove == true);
    REQUIRE(easyVector.size() == 28);

    didRemove = easyVector.removeLastOccurrenceOfItem(5);
    REQUIRE ( didRemove == true);
    REQUIRE(easyVector.size() == 27);

    didRemove = easyVector.removeLastOccurrenceOfItem(5);
    REQUIRE ( didRemove == false);
    REQUIRE(easyVector.size() == 27);
}


// static void testRemoveAllOccurrenceOfItems() {
//     easy_vector<int> container;
//     for ( int i =0 ; i < 30; i++){
//         container.push_back(i%10);
//     }
//     container.push_back(11);
//     REQUIRE( container.size() == 31);
//     long count = container.removeAllOccurrenceOfItems(99);
//     REQUIRE( count == 0);
//     REQUIRE( container.size() == 31);
//
//     count = container.removeAllOccurrenceOfItems(11);
//     REQUIRE( count == 1);
//     REQUIRE( container.size() == 30);
//
//     count = container.removeAllOccurrenceOfItems(3);
//     std::cout << container.toString() << std::endl;
//     REQUIRE( count == 3);
//     REQUIRE( container.size() == 27);
// }


 

TEST_CASE("testRemoveAllOccurrenceOfItems","[0]" ) {
    easy_vector<int> easyVector;
    for ( int i =0 ; i < 30; i++){
        easyVector.push_back(i % 10);
    }
    REQUIRE(easyVector.size() == 30);

    auto didRemove = easyVector.removeLastOccurrenceOfItem(5);
    REQUIRE ( didRemove == true);
    REQUIRE(easyVector.size() == 29);

    didRemove = easyVector.removeLastOccurrenceOfItem(5);
    REQUIRE ( didRemove == true);
    REQUIRE(easyVector.size() == 28);

    didRemove = easyVector.removeLastOccurrenceOfItem(5);
    REQUIRE ( didRemove == true);
    REQUIRE(easyVector.size() == 27);

    didRemove = easyVector.removeLastOccurrenceOfItem(5);
    REQUIRE ( didRemove == false);
    REQUIRE(easyVector.size() == 27);
}


TEST_CASE("testChaining" ) {
    easy_array<int,100> container;
    for ( int i =0 ; i < 100; i++){
        container[i]  = i;
    }
    container.filter([](int i){
        return i%2 == 0;
    }).map<double>([](int i){
        return 2 * M_PI * i;
    }).forEach([](double d){
        static int i = 0;
        std::cout << i  << ":" <<  d << std::endl;
        i = i +2;
    });
}

