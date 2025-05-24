#pragma once

#include <string>
#include <sstream>
#include <array>
#include <algorithm>
#include <random>
#include <chrono>
#include <iostream>
#include <iterator>
#include <cmath>
#include "easy_vector.h"

namespace dsj {

    template<typename T, int N>
    class easy_array {

        std::array<T, N> arr;

    public:
        easy_array() = default;
        explicit easy_array(const std::array<T, N>& input) : arr(input) {}

        std::size_t size() const { return N; }

        std::array<T, N>& data() { return arr; }
        const std::array<T, N>& data() const { return arr; }

        T& operator[](std::size_t index) { return arr[index]; }
        const T& operator[](std::size_t index) const { return arr[index]; }

        // Iterators
        auto begin() { return arr.begin(); }
        auto end() { return arr.end(); }
        auto begin() const { return arr.begin(); }
        auto end() const { return arr.end(); }
        auto rbegin() { return arr.rbegin(); }
        auto rend() { return arr.rend(); }
        auto rbegin() const { return arr.rbegin(); }
        auto rend() const { return arr.rend(); }
        auto cbegin() const { return arr.cbegin(); }
        auto cend() const { return arr.cend(); }

        // toString
        std::string toString() const {
            std::ostringstream ss;
            ss << "[";
            forEach([&](const T& elem) {
                ss << elem << ",";
            });
            if (!arr.empty()) ss.seekp(-1, std::ios_base::end);  // remove last comma
            ss << "]";
            return ss.str();
        }

        friend std::ostream& operator<<(std::ostream& out, const easy_array<T, N>& ea) {
            out << ea.toString();
            return out;
        }

        // Functional Iteration
        template<typename Func>
        void forEach(Func&& func) {
            std::for_each(arr.begin(), arr.end(), std::forward<Func>(func));
        }

        template<typename Func>
        void forEach(Func&& func) const {
            std::for_each(arr.cbegin(), arr.cend(), std::forward<Func>(func));
        }

        template<typename Func>
        void forEachReverse(Func&& func) {
            std::for_each(arr.rbegin(), arr.rend(), std::forward<Func>(func));
        }

        template<typename Func>
        void forEachReverse(Func&& func) const {
            std::for_each(arr.crbegin(), arr.crend(), std::forward<Func>(func));
        }

        // Convert to easy_vector (useful for operations that shrink)
        easy_vector<T> toEasyVector() const {
            easy_vector<T> result;
            for (const auto& elem : arr) result.push_back(elem);
            return result;
        }

        // Unique
        easy_vector<T> unique() const {
            return toEasyVector().unique();
        }

        // Filter: returns easy_vector because size may shrink
        template<typename Predicate>
        easy_vector<T> filter(Predicate&& predicate) const {
            easy_vector<T> result;
            for (const auto& elem : arr) {
                if (predicate(elem)) result.push_back(elem);
            }
            return result;
        }

        // Map to same size easy_array<U, N>
        template<typename U, typename Func>
        easy_array<U, N> map(Func&& func) const {
            easy_array<U, N> result;
            for (std::size_t i = 0; i < N; ++i) {
                result[i] = func(arr[i]);
            }
            return result;
        }

        template<typename Func>
        void transform_inplace(Func&& func) {
            for (auto& elem : arr) {
                elem = func(elem);
            }
        }

        void reverse() {
            std::reverse(arr.begin(), arr.end());
        }

        void shuffle() {
            auto seed = std::chrono::system_clock::now().time_since_epoch().count();
            std::shuffle(arr.begin(), arr.end(), std::default_random_engine(seed));
        }

        void sort() {
            std::sort(arr.begin(), arr.end());
        }

        template<typename Compare>
        void sort(Compare&& comp) {
            std::sort(arr.begin(), arr.end(), std::forward<Compare>(comp));
        }

        std::ptrdiff_t indexOf(const T& item) const {
            auto it = std::find(arr.begin(), arr.end(), item);
            return (it != arr.end()) ? std::distance(arr.begin(), it) : -1;
        }
    };

}
