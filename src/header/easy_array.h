//
// Created by Daniel St. John on 12/25/20.
//

#pragma once

#include <string>
#include <sstream>
#include <array>
#include <algorithm>
#include <memory>
#include <random>       // std::default_random_engine
#include <chrono>       // std::chrono::system_clock
#include "easy_vector.h"


namespace dsj::array {

    template<typename T, int N>
    class easy_array : public std::array<T, N> {

    public:

        std::string  toString(){
            std::stringstream ss;
            ss << "[" ;
            forEach([&] (T  elem){
                ss << elem << ",";
            });
            // The toString() method inserts a trailing comma after the last
            // element of the array. You may want to handle this case in a special
            // way in order to avoid the trailing comma.
            ss << "]" << std::endl;
            return ss.str();
        }


        friend std::ostream &operator<<(std::ostream &out, const easy_array<T,N> &c){
            out << c.toString();
            return out;
        }


        void forEach(std::function<void(T &element)> selector) {
            std::for_each(this->begin(), this->end(), selector);
        }

        void forEachReverse( std::function<  void(T & element)> selector) {
            std::for_each(this->rbegin(), this->rend(), [&](T& elem) {
                selector(elem);
            });
        }


        easy_vector<T> toEasyVector() {
            easy_vector<T>  copy;
            forEach( [&](T elem){
                copy.push_back(elem);
            });
            return copy;
        }

        easy_vector<T> unique() {
            easy_vector<T>  copy;
            forEach( [&](T elem){
                copy.push_back(elem);
            });
            return copy.unique();
        }
 
        
        easy_vector<T> filter(std::function<  bool(T & element)> selector) {
            easy_vector<T>  v ;
            easy_vector<T>  copy;
            forEach( [&](T elem){
                copy.push_back(elem);
            });
            return copy.filter(selector);
        }


        // TODO : DRY
        template<typename U>
        std::unique_ptr < std::array<U,N> > mapSmart(std::function<  U (T & element)> selector) {
            std::unique_ptr < std::array<T,N> > v(new std::array< T ,N>());
            size_t index = 0;
            std::for_each(begin(this), end(this), [&](T& elem) {
                v[index] = (selector(elem));
            });
            return std::move(v);
        }

        template<typename U> easy_array<U,N>
        map(std::function<  U (T & element)> selector) {
            easy_array<U,N> v;
            auto it = this->begin();
            auto end = this->end();
            for ( auto i =0; it != end; i++, it++){
                v[i] = selector(*it);
             }
            return  v;
        }

        void reverse() {
            std::reverse(begin(*this),end(*this));
        }

        void shuffle () {
            using namespace std::chrono;
            auto seed = system_clock::now().time_since_epoch().count();
            std::shuffle (begin(*this), end(*this), std::default_random_engine(seed));
        }
     
        void sort (){
            std::sort(begin(*this), end(*this));
        }

        void sort (std::function<  bool (T & a, T & b) > selector ){
            std::sort(begin(*this), end(*this),selector);
        }

        // javascript like api get the index of item
        long indexOf(T item){
            long index = -1;
            auto start = std::begin(*this);
            auto end = std::end(*this);
            auto it = std::find(start,end, item );
            if ( it != end){
               index= it - start;
            }
            return index;
        }

    };




    /*
     * Inheritance from STL containers: The class easy_array continues to directly inherit from
     * std::array. This approach is not typically recommended in C++ due to potential risks and
     * the fact that STL containers were not designed to be inherited.
     *
     * here's how you might rewrite your easy_array class to use composition rather than inheritance.
     * In this case, we include std::array<T, N> as a member of easy_array, instead of inheriting:
     */
    template<typename T, int N>
    class easy_array2 {
        std::array<T, N> arr;  // Composition: include std::array as a member
    public:

        auto& data() { return arr; }
        const auto& data() const { return arr; }

        // Add begin() and end() forwarders
        auto begin() { return arr.begin(); }
        auto end() { return arr.end(); }
        auto begin() const { return arr.begin(); }
        auto end() const { return arr.end(); }
        auto cbegin() const { return arr.cbegin(); }
        auto cend() const { return arr.cend(); }



        // Other methods remain mostly the same except where they access the array
        std::string toString(){
            std::stringstream ss;
            ss << "[" ;
            std::for_each(arr.begin(), arr.end(), [&](T elem){ ss << elem << ","; });
            ss << "]" << std::endl;
            return ss.str();
        }

        // And so on for your other methods. Whenever you were using a method on 'this',
        // you now use it on 'arr' instead. For example,

        void forEach(std::function<void(T &element)> selector) {
            std::for_each(arr.begin(), arr.end(), selector);
        }

        void reverse() {
            std::reverse(arr.begin(), arr.end());
        }
        // And so on...
    };


}
