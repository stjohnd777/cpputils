#pragma once

#include <string>
#include <sstream>
#include <map>
#include <algorithm>
#include <iostream>
#include "easy_vector.h"

namespace dsj {

    template<typename T, typename U>
    class easy_map {
        std::map<T, U> internal_map;

    public:
        easy_map() = default;
        explicit easy_map(const std::map<T, U>& input) : internal_map(input) {}

        std::map<T, U>& data() { return internal_map; }
        const std::map<T, U>& data() const { return internal_map; }

        U& operator[](const T& key) { return internal_map[key]; }
        const U& operator[](const T& key) const { return internal_map.at(key); }

        auto begin() { return internal_map.begin(); }
        auto end() { return internal_map.end(); }
        auto begin() const { return internal_map.begin(); }
        auto end() const { return internal_map.end(); }
        auto rbegin() { return internal_map.rbegin(); }
        auto rend() { return internal_map.rend(); }
        auto rbegin() const { return internal_map.rbegin(); }
        auto rend() const { return internal_map.rend(); }
        auto cbegin() const { return internal_map.cbegin(); }
        auto cend() const { return internal_map.cend(); }

        std::string toString() const {
            std::ostringstream ss;
            ss << "{";
            forEach([&](const auto& pair) {
                ss << "(" << pair.first << ":" << pair.second << "),";
            });
            if (!internal_map.empty()) ss.seekp(-1, std::ios_base::end);
            ss << "}";
            return ss.str();
        }

        friend std::ostream& operator<<(std::ostream& out, const easy_map<T, U>& map) {
            out << map.toString();
            return out;
        }

        template<typename Func>
        void forEach(Func&& func) {
            std::for_each(internal_map.begin(), internal_map.end(), std::forward<Func>(func));
        }

        template<typename Func>
        void forEach(Func&& func) const {
            std::for_each(internal_map.cbegin(), internal_map.cend(), std::forward<Func>(func));
        }

        template<typename Func>
        void forEachReverse(Func&& func) {
            std::for_each(internal_map.rbegin(), internal_map.rend(), std::forward<Func>(func));
        }

        template<typename Func>
        void forEachReverse(Func&& func) const {
            std::for_each(internal_map.crbegin(), internal_map.crend(), std::forward<Func>(func));
        }

        easy_vector<T> getKeys() const {
            easy_vector<T> keys;
            for (const auto& [key, _] : internal_map) {
                keys.push_back(key);
            }
            return keys;
        }

        easy_vector<U> getValues() const {
            easy_vector<U> values;
            for (const auto& [_, value] : internal_map) {
                values.push_back(value);
            }
            return values;
        }

        template<typename Predicate>
        easy_map<T, U> filter(Predicate&& predicate) const {
            easy_map<T, U> result;
            for (const auto& pair : internal_map) {
                if (predicate(pair)) {
                    result[pair.first] = pair.second;
                }
            }
            return result;
        }

        template<typename TT, typename UU, typename Transformer>
        easy_map<TT, UU> map(Transformer&& transformer) const {
            easy_map<TT, UU> result;
            for (const auto& pair : internal_map) {
                auto newPair = transformer(pair);
                result[newPair.first] = newPair.second;
            }
            return result;
        }

        std::map<T, U> unique() const {
            return internal_map;
        }

        // NEW: Check for key
        bool has(const T& key) const {
            return internal_map.find(key) != internal_map.end();
        }

        // NEW: Check for value
        bool containsValue(const U& value) const {
            return std::any_of(
                internal_map.begin(), internal_map.end(),
                [&](const auto& pair) { return pair.second == value; });
        }

        // NEW: Merge with another map (right overwrites left)
        easy_map<T, U> merge(const easy_map<T, U>& other) const {
            easy_map<T, U> result = *this;
            for (const auto& [k, v] : other.internal_map) {
                result[k] = v;
            }
            return result;
        }

        // NEW: Invert map (value becomes key)
        // Assumes U is unique and hashable/comparable
        easy_map<U, T> invert() const {
            easy_map<U, T> result;
            for (const auto& [k, v] : internal_map) {
                result[v] = k;
            }
            return result;
        }
    };

}
