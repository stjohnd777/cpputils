//
//  easy_common.cpp
//  EasyCppUtils
//
//  Created by Daniel St. John on 4/13/21.
//

#include "../header/easy_common.h"

#include <iostream>
#include <functional>
#include <array>
#include <vector>
#include <map>
#include <algorithm>
#include <memory>
#include <random>       // std::default_random_engine
#include <chrono>       // std::chrono::system_clock

namespace dsj {

    template<typename T >
    void forEach(std::vector<T> subject, std::function<void(T &element)> selector) {
        std::for_each(begin(subject), end(subject), [&](T &elem) { selector(elem); });
    }

    template<typename T >
    bool swap_if(T a, T b, std::function< bool(T & a, T & b)> isSwap) {
        bool didSwap = false;
        if (isSwap(a, b)) {
            std::swap(a, b);
            didSwap = true;
        }
        return didSwap;
    }

    template <typename T>
    std::vector<T> filter(std::vector<T> subject, std::function<  bool(T& element)> selector) {
        std::vector<T> filteredVector;
        std::for_each(begin(filteredVector), end(filteredVector), [&](T& elem) {
            if (selector(elem)) {
                filteredVector.push_back(elem);
            }
        });
        return filteredVector;
    }

    template <typename T>
    T* filter ( T* subject, std::function<  bool(T& element)> selector) {
        std::vector<T> filteredVector;
        std::for_each(begin(filteredVector), end(filteredVector), [&](T& elem) {
            if (selector(elem)) {
                filteredVector.push_back(elem);
            }
        });
        T t[filteredVector.size()];
        size_t index =0;
        std::for_each(begin(t),end(t),[&](T aT){
            t[index] = aT;
            t++;
        });
        return t;
    }

    template <typename T>
    std::vector<T> map(std::vector<T> subject, std::function< T (T element)> selector) {
        std::vector<T> filteredVector;
        std::for_each(begin(filteredVector), end(filteredVector), [&] (T& elem) {
            filteredVector.push_back(selector(elem));
        });
        return filteredVector;
    }

    template <class T>
    std::vector<T>  removeDups( std::vector<T>  source) {
        std::vector<T>  copy = source;
        std::sort(std::begin(copy), std::end(copy));
        auto last = std::unique(begin(copy), end(copy));
        copy.erase(last, copy.end());
        return   copy ;
    }

    template <class T>
    std::vector<T> shuffle ( std::vector<T> source) {
        using namespace std::chrono;
        std::vector<T>  copy = source;
        auto seed = system_clock::now().time_since_epoch().count();
        std::shuffle (begin(copy), end(copy), std::default_random_engine(seed));
        return copy;
    }


}
