#pragma once

#include <vector>
#include <algorithm>
#include <random>
#include <string>
#include <sstream>

namespace dsj {

    template<typename T>
    class easy_vector {

    private:
        std::vector<T> internal_vector;

    public:
        easy_vector() = default;
        explicit easy_vector(const std::vector<T>& input) : internal_vector(input) {}

        static easy_vector<T> from(std::initializer_list<T> il) {
            return easy_vector<T>(std::vector<T>(il));
        }

        // Output
        std::string toString() const {
            std::ostringstream ss;
            ss << "[";
            forEach([&](const T& elem) {
                ss << elem << ",";
            });
            if (!internal_vector.empty()) {
                ss.seekp(-1, std::ios_base::end); // Remove the last comma
            }
            ss << "]";
            return ss.str();
        }

        friend std::ostream& operator<<(std::ostream& out, const easy_vector<T>& v) {
            out << v.toString();
            return out;
        }

        // Functional Iteration
        template<typename Func>
        void forEach(Func&& func) {
            std::for_each(internal_vector.begin(), internal_vector.end(), std::forward<Func>(func));
        }

        template<typename Func>
        void forEach(Func&& func) const {
            std::for_each(internal_vector.begin(), internal_vector.end(), std::forward<Func>(func));
        }

        template<typename Func>
        void forEachReverse(Func&& func) {
            std::for_each(internal_vector.rbegin(), internal_vector.rend(), std::forward<Func>(func));
        }

        template<typename Func>
        void forEachReverse(Func&& func) const {
            std::for_each(internal_vector.rbegin(), internal_vector.rend(), std::forward<Func>(func));
        }

        // Transformations
        easy_vector<T> unique() const {
            easy_vector<T> copy;
            copy.internal_vector = internal_vector;
            std::sort(copy.internal_vector.begin(), copy.internal_vector.end());
            auto last = std::unique(copy.internal_vector.begin(), copy.internal_vector.end());
            copy.internal_vector.erase(last, copy.internal_vector.end());
            return copy;
        }

        template<typename Predicate>
        easy_vector<T> filter(Predicate&& predicate) const {
            easy_vector<T> result;
            for (const auto& elem : internal_vector) {
                if (predicate(elem)) {
                    result.internal_vector.push_back(elem);
                }
            }
            return result;
        }


        template<typename U, typename Func>
        easy_vector<U> map(Func&& func) const {
            easy_vector<U> result;
            for (const auto& elem : internal_vector) {
                result.data().push_back(func(elem));
            }
            return result;
        }


        template<typename Func>
        void transform_inplace(Func&& func) {
            for (auto& elem : internal_vector) {
                elem = func(elem);
            }
        }

        // Mutators
        void reverse() {
            std::reverse(internal_vector.begin(), internal_vector.end());
        }

        void shuffle() {
            using namespace std::chrono;
            auto seed = system_clock::now().time_since_epoch().count();
            std::shuffle(internal_vector.begin(), internal_vector.end(), std::default_random_engine(seed));
        }

        void sort() {
            std::sort(internal_vector.begin(), internal_vector.end());
        }

        template<typename Compare>
        void sort(Compare&& comparator) {
            std::sort(internal_vector.begin(), internal_vector.end(), std::forward<Compare>(comparator));
        }

        // Search and Removal
        std::ptrdiff_t indexOf(const T& item) const {
            auto it = std::find(internal_vector.begin(), internal_vector.end(), item);
            if (it != internal_vector.end()) {
                return std::distance(internal_vector.begin(), it);
            }
            return -1;
        }

        bool removeFirstOccurrenceOfItem(const T& item) {
            auto it = std::find(internal_vector.begin(), internal_vector.end(), item);
            if (it != internal_vector.end()) {
                internal_vector.erase(it);
                return true;
            }
            return false;
        }

        bool removeLastOccurrenceOfItem(const T& item) {
            for (auto it = internal_vector.rbegin(); it != internal_vector.rend(); ++it) {
                if (*it == item) {
                    internal_vector.erase(std::next(it).base());
                    return true;
                }
            }
            return false;
        }

        long removeAllOccurrencesOfItem(const T& item) {
            auto oldSize = internal_vector.size();
            internal_vector.erase(
                std::remove(internal_vector.begin(), internal_vector.end(), item),
                internal_vector.end()
            );
            return oldSize - internal_vector.size();
        }

        // STL-like Interface
        void push(const T& value) { internal_vector.push_back(value); }
        void push(T&& value) { internal_vector.push_back(std::move(value)); }
        void push_back(const T& value) { push(value); }
        void push_back(T&& value) { push(std::move(value)); }

        template<typename... Args>
        void emplace_back(Args&&... args) {
            internal_vector.emplace_back(std::forward<Args>(args)...);
        }

        void pop_back() { internal_vector.pop_back(); }

        template <typename InputIt>
        void insert(typename std::vector<T>::iterator pos, InputIt first, InputIt last) {
            internal_vector.insert(pos, first, last);
        }

        void insert(typename std::vector<T>::iterator pos, const T& value) {
            internal_vector.insert(pos, value);
        }

        void insert(typename std::vector<T>::iterator pos, T&& value) {
            internal_vector.insert(pos, std::move(value));
        }

        void insert(typename std::vector<T>::iterator pos, std::initializer_list<T> il) {
            internal_vector.insert(pos, il);
        }

        void erase(typename std::vector<T>::iterator pos) {
            internal_vector.erase(pos);
        }

        void erase(typename std::vector<T>::iterator first, typename std::vector<T>::iterator last) {
            internal_vector.erase(first, last);
        }

        T& front() { return internal_vector.front(); }
        const T& front() const { return internal_vector.front(); }

        T& back() { return internal_vector.back(); }
        const T& back() const { return internal_vector.back(); }

        T& at(std::size_t index) { return internal_vector.at(index); }
        const T& at(std::size_t index) const { return internal_vector.at(index); }

        void swap(easy_vector<T>& other) { internal_vector.swap(other.internal_vector); }
        void clear() { internal_vector.clear(); }

        std::vector<T>& data() { return internal_vector; }
        const std::vector<T>& data() const { return internal_vector; }

        T& operator[](std::size_t index) { return internal_vector[index]; }
        const T& operator[](std::size_t index) const { return internal_vector[index]; }

        std::size_t size() const { return internal_vector.size(); }
        bool empty() const { return internal_vector.empty(); }

        std::size_t capacity() const { return internal_vector.capacity(); }
        void reserve(std::size_t n) { internal_vector.reserve(n); }
        void shrink_to_fit() { internal_vector.shrink_to_fit(); }
        void resize(std::size_t n) { internal_vector.resize(n); }
        void resize(std::size_t n, const T& value) { internal_vector.resize(n, value); }

        // Operators
        bool operator==(const easy_vector<T>& other) const { return internal_vector == other.internal_vector; }
        bool operator!=(const easy_vector<T>& other) const { return internal_vector != other.internal_vector; }
        bool operator<(const easy_vector<T>& other) const { return internal_vector < other.internal_vector; }
        bool operator<=(const easy_vector<T>& other) const { return internal_vector <= other.internal_vector; }
        bool operator>(const easy_vector<T>& other) const { return internal_vector > other.internal_vector; }
        bool operator>=(const easy_vector<T>& other) const { return internal_vector >= other.internal_vector; }

        // Iterators
        auto begin() { return internal_vector.begin(); }
        auto end() { return internal_vector.end(); }
        auto begin() const { return internal_vector.begin(); }
        auto end() const { return internal_vector.end(); }
        auto rbegin() { return internal_vector.rbegin(); }
        auto rend() { return internal_vector.rend(); }
        auto rbegin() const { return internal_vector.rbegin(); }
        auto rend() const { return internal_vector.rend(); }

    };

} // namespace dsj
