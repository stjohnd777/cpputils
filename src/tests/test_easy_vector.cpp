//
// Created by Daniel St. John on 12/6/20.
//
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../header/easy_vector.h"

using namespace std;
using namespace dsj;

TEST_CASE( "begin-end", "[std::begin,end]") {

    easy_vector<int> ev;
    for ( int i =0 ; i < 10; i++){
        ev.push_back(i);
    }

    int index = 0;
    for ( auto it = begin(ev); it!=end(ev);it++){
        REQUIRE( *it == index );
        index++;
    }
}
TEST_CASE( "easy_vector", "[std::for_each]") {

    easy_vector<int> ev;
    for ( int i =0 ; i < 10; i++){
        ev.push_back(i);
    }

    std::for_each(begin(ev),end(ev),[&](int i){
        cout << i << endl;
    });

    std::for_each(ev.begin(),ev.end(),[&](int i){
        cout << i << endl;
    });

}

TEST_CASE( "easy_vector.forEach", "[forEach]") {
    easy_vector<int> ev;
    for ( int i =0 ; i < 10; i++){
        ev.push_back(i);
    }
    int index = 0;
    ev.forEach( [&](int i){
        REQUIRE( i == index );
        index++;
    });
}

TEST_CASE( "easy_vector.forEachReverse", "[forEach]") {
    easy_vector<int> ev;
    for ( int i =0 ; i < 10; i++){
        ev.push_back(i);
    }
    int index = 9;
    ev.forEachReverse( [&](int i){
        REQUIRE( i == index );
        index--;
    });
}

TEST_CASE( "easy_vector.filter", "[forEach]") {
    easy_vector<int> ev;
    for ( int i =0 ; i < 10; i++){
        ev.push_back(i);
    }

    auto evens = ev.filter( [&](int i){
        return i%2 == 0;
    });

    evens.forEach( [&](int i){
        REQUIRE( i % 2 == 0 );
    });
}

TEST_CASE( "easy_vector.map", "[forEach]") {
    easy_vector<int> ev;
    for ( int i =0 ; i < 10; i++){
        ev.push_back(i);
    }

//    auto evens = ev.map<float>( [&](int i){
//        return sqrt((float)i) ;
//    });

//    int index = 0;
//    evens.forEach( [&](float f){
//        REQUIRE( sqrt((float )index) == f );
//        index++;
//    });
}

TEST_CASE( "easy_vector.reverse", "[reverse]") {
    easy_vector<int> ev;
    for ( int i =0 ; i < 10; i++){
        ev.push_back(i);
    }

    ev.reverse();

    int index = 9;
    ev.forEach( [&](int i){
        cout << index  << ":" << i << endl;
        REQUIRE( i == index );
        index--;
    });
}

TEST_CASE( "easy_vector.shuffle", "[shuffle]") {

    easy_vector<int> ev;
    for ( int i =0 ; i < 10; i++){
        ev.push_back(i);
    }

    ev.shuffle();

    int index = 0;
    ev.forEach( [&](int i){
        cout << index  << ":" << i << endl;
        index++;
    });
}

TEST_CASE("easy_vector.indexOf","[indexOf]"){

    easy_vector<int> ev;
    for ( int i =0 ; i < 10; i++){
        ev.push_back(i);
    }

    auto index = ev.indexOf(5);
    REQUIRE( index ==5);

    index = ev.indexOf(1005);
    REQUIRE( index ==-1);
}

TEST_CASE("easy_vector.removeFirstItem","[removeFirstOccurrenceOfItem]"){
    // TODO: more extensive testing here
    easy_vector<int> ev;
    for ( int i =0 ; i < 10; i++){
        ev.push_back(i);
    }
    auto didRemove = ev.removeFirstOccurrenceOfItem(0);
    REQUIRE ( didRemove == true);
    int index = ev.indexOf(0);
    REQUIRE( index ==-1);
}

