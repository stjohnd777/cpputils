//
// Created by Daniel St. John on 12/6/20.
//

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <iostream>
using namespace std;

#include "../header/easy_string.h"

TEST_CASE("easy_string.startWith", "[001]") {

    dsj::easy_string es("001ndfjbwqfjwqb001");
    bool b = es.startsWith("001");
    REQUIRE( b == true);
}


TEST_CASE("easy_string.endWith", "[001]") {

    dsj::easy_string es("001ndfjbwqfjwqbffb001");
    bool b = es.endsWith("001");
    REQUIRE( b == true);
}


TEST_CASE("easy_string.contains", "[HERE]") {

    dsj::easy_string es("001ndfjHEREfjwqbffb");
    bool b = es.contains("HERE");
    REQUIRE( b == true);
}

TEST_CASE("easy_string.revers", "[HERE]") {

    dsj::easy_string es("12345");
    es.reverse();
    REQUIRE( es == "54321");
}

TEST_CASE("easy_string.replaceAllSubstrings", "[3x001]") {

    dsj::easy_string es("001ndfj001fjwqbffb001");
    es = es.replaceAllSubstrings("001","HERE");
    REQUIRE( es == "HEREndfjHEREfjwqbffbHERE");
}

TEST_CASE("easy_string.split", "[delim]") {

    dsj::easy_string es("001|002|003");
    auto v = es.split('|');
    REQUIRE( v.size() == 3);
    REQUIRE( v[0] == "001");
    REQUIRE( v[1] == "002");
    REQUIRE( v[2] == "003");
}

TEST_CASE("easy_string.split2", "[delim]") {

    dsj::easy_string es("|001|002|003||");
    auto v = es.split('|');
    //REQUIRE( v.size() == 3);
    cout << v.size() << endl;
    for ( auto s : v){
        cout << s << endl;
    }
    REQUIRE( v[0] == "001");
    REQUIRE( v[1] == "002");
    REQUIRE( v[2] == "003");
}

TEST_CASE("easy_string.toUpperCase", "[toUpperCase]") {
    dsj::easy_string s("make me uppercase");
    s.toUpperCase();
    REQUIRE( s == "MAKE ME UPPERCASE");
}

TEST_CASE("easy_string.toLowerCase", "[toLowerCase]") {
    dsj::easy_string s("ASDFG");
    s.toLowerCase();
    REQUIRE( s == "asdfg");
}

TEST_CASE("easy_string.trim", "[trim]") {
    dsj::easy_string s("    Daniel");
    cout << "before:" << s << endl;
    s.trim();
    cout << "after:" <<  s << endl;
    REQUIRE( s == "Daniel");
}