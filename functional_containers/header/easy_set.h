#pragma once

#include <set>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <iostream>
#include "easy_vector.h"

namespace dsj {

    template<typename T>
    class easy_set {
        std::set<T> internal_set;

    public:
        easy_set() = default;
        explicit easy_set(const std::set<T>& input) : internal_set(input) {}

        std::set<T>& data() { return internal_set; }
        const std::set<T>& data() const { return internal_set; }

        std::size_t size() const { return internal_set.size(); }
        bool empty() const { return internal_set.empty(); }

        bool has(const T& value) const {
            return internal_set.find(value) != internal_set.end();
        }

        void insert(const T& value) {
            internal_set.insert(value);
        }

        void erase(const T& value) {
            internal_set.erase(value);
        }

        void clear() {
            internal_set.clear();
        }

        // Iterators
        auto begin() { return internal_set.begin(); }
        auto end() { return internal_set.end(); }
        auto begin() const { return internal_set.begin(); }
        auto end() const { return internal_set.end(); }
        auto rbegin() { return internal_set.rbegin(); }
        auto rend() { return internal_set.rend(); }
        auto rbegin() const { return internal_set.rbegin(); }
        auto rend() const { return internal_set.rend(); }

        // toString
        std::string toString() const {
            std::ostringstream ss;
            ss << "{";
            forEach([&](const T& elem) {
                ss << elem << ",";
            });
            if (!internal_set.empty()) ss.seekp(-1, std::ios_base::end);
            ss << "}";
            return ss.str();
        }

        friend std::ostream& operator<<(std::ostream& out, const easy_set<T>& s) {
            out << s.toString();
            return out;
        }

        // Functional iteration
        template<typename Func>
        void forEach(Func&& func) {
            std::for_each(internal_set.begin(), internal_set.end(), std::forward<Func>(func));
        }

        template<typename Func>
        void forEach(Func&& func) const {
            std::for_each(internal_set.begin(), internal_set.end(), std::forward<Func>(func));
        }

        template<typename Func>
        void forEachReverse(Func&& func) {
            std::for_each(internal_set.rbegin(), internal_set.rend(), std::forward<Func>(func));
        }

        template<typename Func>
        void forEachReverse(Func&& func) const {
            std::for_each(internal_set.rbegin(), internal_set.rend(), std::forward<Func>(func));
        }

        // Filter
        template<typename Predicate>
        easy_set<T> filter(Predicate&& predicate) const {
            easy_set<T> result;
            for (const auto& elem : internal_set) {
                if (predicate(elem)) {
                    result.insert(elem);
                }
            }
            return result;
        }

        // Map
        template<typename U, typename Func>
        easy_set<U> map(Func&& func) const {
            easy_set<U> result;
            for (const auto& elem : internal_set) {
                result.insert(func(elem));
            }
            return result;
        }

        // Convert to easy_vector
        easy_vector<T> toVector() const {
            easy_vector<T> result;
            for (const auto& elem : internal_set) {
                result.push_back(elem);
            }
            return result;
        }

        // Set operations
        easy_set<T> merge(const easy_set<T>& other) const {
            easy_set<T> result = *this;
            result.internal_set.insert(other.begin(), other.end());
            return result;
        }

        easy_set<T> intersect(const easy_set<T>& other) const {
            easy_set<T> result;
            for (const auto& elem : internal_set) {
                if (other.has(elem)) {
                    result.insert(elem);
                }
            }
            return result;
        }

        easy_set<T> subtract(const easy_set<T>& other) const {
            easy_set<T> result;
            for (const auto& elem : internal_set) {
                if (!other.has(elem)) {
                    result.insert(elem);
                }
            }
            return result;
        }
    };

}
