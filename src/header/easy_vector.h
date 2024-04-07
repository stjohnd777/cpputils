#pragma once

#include "easy_common.h"


#include <vector>

#include <iostream>
#include <functional>
#include <array>

#include <map>
#include <algorithm>
#include <memory>
#include <random>       // std::default_random_engine
#include <chrono>       // std::chrono::system_clock
#include <string>
#include <sstream>

#include <memory>

#define WORK_AROND_0 = 1
namespace dsj {

	template<typename T>
	class easy_vector : public std::vector<T> {

	public:
        
        // TODO : DRY
        friend std::ostream &operator<<(std::ostream &out, const easy_vector &v);
        
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
        
        // TODO : DRY
        void forEach( std::function<  void(T & element)> selector) {
            std::for_each(this->begin(), this->end(), [&](T& elem) {
                selector(elem);
            });
        }

        // TODO : DRY
        void forEachReverse( std::function<  void(T & element)> selector) {
            std::for_each(this->rbegin(), this->rend(), [&](T& elem) {
                selector(elem);
            });
        }
        
        // TODO : DRY
        easy_vector<T> unique() {
            easy_vector<T>  copy ;
            copy = *this;
            std::sort(begin(copy), end(copy));
            auto last = std::unique(begin(copy), end(copy));
            copy.erase(last, copy.end());
            return copy;
        }
        
        // TODO : DRY
        easy_vector<T> filter(std::function<  bool(T & element)> selector) {
           easy_vector<T>  v ;
           std::for_each(begin(*this), end(*this), [&](T& elem) {
               if (selector(elem)) {
                   v.push_back(elem);
               }
           });
           return v;
        }


        template<typename U>
        easy_vector<U> map(std::function<U(T & element)> selector){
            easy_vector<U> v;
            for_each(begin(*this), end(*this), [&](T& elem) {
                v.push_back(selector(elem));
            });
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

        void  sort (std::function<  bool (T & a, T & b) > selector ){
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

        /// remove the first occurrence of the item starting
        /// from back of the container
        bool removeFirstOccurrenceOfItem (T item){
            auto it = std::find(std::begin(*this),std::end(*this),item);
            if (it!=std::end(*this)){
               this->erase(it);
               return true;
            }
            return false;
        }

        /// remove the last occurrence of the item starting
        /// from back of the container
        bool removeLastOccurrenceOfItem (T item){
            
#if WORKAROUND_0
            auto it= end(*this);
        
            while ( it > begin(*this))
            {
                auto value = *it;
                if ( value == item) {
                    it = this->erase(it);
                    this->resize(this->size());
                    return true;
                }
                it--;
            }
            return false;
#else
            auto it = std::find(std::rbegin(*this),std::rend(*this),item);
            if (it!=std::rend(*this)){
                // TODO :: WFT
                //this->erase(it);
                return true;
            }
            return false;
#endif
        }
        
        /// remove  all  occurrence of the item
        /// this can be done with filter
        long removeAllOccurrenceOfItems( T item){
            // TODO : change signature to take a lambda that will be executed when occurrence is encountered
            // TODO : with default null
            long counter = 0;
            while(removeFirstOccurrenceOfItem(item) == true){
                counter ++;
            }
            return counter;
        }
    };



    template<typename T>
    std::ostream &operator<<(std::ostream &out, const easy_vector<T> &c);
}


