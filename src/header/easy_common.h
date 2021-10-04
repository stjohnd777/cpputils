//
// Created by Daniel St. John on 3/22/21.
//

#pragma once
 


#include <vector>

namespace dsj {

    template<typename T >
    void forEach(std::vector<T> subject, std::function<void(T &element)> selector);

    template<typename T >
    bool swap_if(T a, T b, std::function< bool(T & a, T & b)> isSwap) ;

    template <typename T>
    std::vector<T> filter(std::vector<T> subject, std::function<  bool(T& element)> selector);

    template <typename T>
    T* filter ( T* subject, std::function<  bool(T& element)> selector) ;

    template <typename T>
    std::vector<T> map(std::vector<T> subject, std::function< T (T element)> selector) ;

    template <class T>
    std::vector<T>  removeDups( std::vector<T>  source) ;

    template <class T>
    std::vector<T> shuffle ( std::vector<T> source) ;

}

//    TODO
//    template<typename  InputIt, typename T >
//    void forEach(InputIt it, std::function<void(T &element)> selector) {
//        std::for_each(InputIt first, InputIt last, [&](T &elem) { selector(elem); });
//    }
