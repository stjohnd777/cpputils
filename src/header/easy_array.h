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
namespace dsj {

    template<typename T, int N>
    class easy_array : public std::array<T, N> {

    public:
        
        // TODO : DRY
        friend std::ostream &operator<<(std::ostream &out, const easy_array<T,N> &c);
 
        // TODO : DRY
        std::string  toString(){
            std::stringstream ss;
            ss << "[" ;
           forEach([&] (T  elem){
                ss << elem << ",";
            });
            ss << "]" << std::endl;
            return ss.str();
        }

        void forEach(std::function<void(T &element)> selector) {
            std::for_each(begin(*this), end(*this), [&](T &elem) {
                selector(elem);
                
            });
        }

        void forEachReverse( std::function<  void(T & element)> selector) {
            std::for_each(this->rbegin(), this->rend(), [&](T& elem) {
                selector(elem);
            });
        }

        
        easy_vector<T> toEasyVectory() {
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
            std::for_each(begin(this), end(this), [&](T& elem) {
                v->push_back(selector(elem));
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

    template<typename T, int N>
    std::ostream &operator<<(std::ostream &out, const easy_array<T,N> &c){
        return c.toString();
    }

}
