#include <catch2/catch_test_macros.hpp>
#include "easy_map.h"
#include "easy_vector.h"
#include <algorithm>
using namespace std;
using dsj::easy_map;
using dsj::easy_vector;



TEST_CASE("easy_map basic functionality", "[easy_map]") {
    easy_map<std::string, int> m;
    m["one"] = 1;
    m["two"] = 2;
    m["three"] = 3;

    SECTION("Element access and size") {
        REQUIRE(m["one"] == 1);
        REQUIRE(m["two"] == 2);
        REQUIRE(m["three"] == 3);
        REQUIRE(m.data().size() == 3);
    }

    SECTION("getKeys and getValues") {
        auto keys = m.getKeys();
        auto values = m.getValues();

        REQUIRE(keys.size() == 3);
        REQUIRE(values.size() == 3);
        REQUIRE(std::find(keys.begin(), keys.end(), "two") != keys.end());
        REQUIRE(std::find(values.begin(), values.end(), 3) != values.end());
    }

    SECTION("forEach iteration") {
        int sum = 0;
        m.forEach([&](const auto& pair) {
            sum += pair.second;
        });
        REQUIRE(sum == 6);
    }

    SECTION("forEachReverse matches reversed keys") {
        std::vector<std::string> keys;
        m.forEachReverse([&](const auto& pair) {
            keys.push_back(pair.first);
        });
        std::reverse(keys.begin(), keys.end());
        auto normalKeys = m.getKeys().data();
        REQUIRE(keys == normalKeys);
    }

    SECTION("filter only evens") {
        auto evenMap = m.filter([](const auto& pair) {
            return pair.second % 2 == 0;
        });

        REQUIRE(evenMap.data().size() == 1);
        REQUIRE(evenMap.has("two"));
        REQUIRE(evenMap["two"] == 2);
    }

    SECTION("map with transformation") {
        auto transformed = m.map<std::string, std::string>([](const auto& pair) {
            return std::make_pair("key_" + pair.first, std::to_string(pair.second * 10));
        });

        REQUIRE(transformed["key_one"] == "10");
        REQUIRE(transformed["key_two"] == "20");
    }

    SECTION("has and containsValue") {
        REQUIRE(m.has("two"));
        REQUIRE_FALSE(m.has("ten"));

        REQUIRE(m.containsValue(3));
        REQUIRE_FALSE(m.containsValue(99));
    }

    SECTION("invert swaps keys and values") {
        auto inverted = m.invert(); // int -> string
        REQUIRE(inverted[1] == "one");
        REQUIRE(inverted[2] == "two");
        REQUIRE(inverted[3] == "three");
    }

    SECTION("merge combines two maps") {
        easy_map<std::string, int> m2;
        m2["four"] = 4;
        m2["two"] = 20; // overwrites original "two"

        auto merged = m.merge(m2);

        REQUIRE(merged["one"] == 1);
        REQUIRE(merged["two"] == 20);
        REQUIRE(merged["four"] == 4);
        REQUIRE(merged.data().size() == 4);
    }

    SECTION("toString outputs something sane") {
        std::string s = m.toString();
        REQUIRE(s.find("one") != std::string::npos);
        REQUIRE(s.find("two") != std::string::npos);
        REQUIRE(s.find("three") != std::string::npos);
    }
}
