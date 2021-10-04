#include "../header/easy_vector.h"


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

namespace dsj {


//    template<typename T>
//    std::string easy_vector<T>::toString(){
//        std::stringstream ss;
//        ss << "[" ;
//       forEach([&] (T  elem){
//            ss << elem << ",";
//        });
//        ss << "]" << std::endl;
//        return ss.str();
//    }
//
//    template<typename T>
//    void easy_vector<T>::forEach( std::function<  void(T & element)> selector) {
//        std::for_each(this->begin(), this->end(), [&](T& elem) {
//            selector(elem);
//        });
//    }

//    template<typename T>
//    void easy_vector<T>::forEachReverse( std::function<  void(T & element)> selector) {
//        std::for_each(this->rbegin(), this->rend(), [&](T& elem) {
//            selector(elem);
//        });
//    }
//
//    template<typename T>
//    void easy_vector<T>::removeAllOccurrenceOfItems( T item){
//        // TODO : change signature to take a lambda that will be executed when occurrence is encountered
//        // TODO : with default null
//         while(removeFirstOccurrenceOfItem(item) );
//    }
//
//    template<typename T>
//    std::unique_ptr<std::vector<T>>  easy_vector<T>::unique() {
//        std::unique_ptr< easy_vector<T> > copy = this;
//        std::sort(begin(copy), end(copy));
//        auto last = std::unique(begin(copy), end(copy));
//        copy.erase(last, copy.end());
//        return std::move( copy );
//    }
//
//    template<typename T>
//    easy_vector<T> easy_vector<T>::filter(std::function<  bool(T & element)> selector) {
//       easy_vector<T>  v ;
//       std::for_each(begin(*this), end(*this), [&](T& elem) {
//           if (selector(elem)) {
//               v.push_back(elem);
//           }
//       });
//       return v;
//    }
//
//
//    template<typename T>
//    void easy_vector<T>::reverse() {
//        std::reverse(begin(*this),end(*this));
//    }
//    template<typename T>
//    void easy_vector<T>::shuffle () {
//        using namespace std::chrono;
//        auto seed = system_clock::now().time_since_epoch().count();
//        std::shuffle (begin(*this), end(*this), std::default_random_engine(seed));
//    }
//
//        template<typename T>
//        std::ostream &operator<<(std::ostream &out, const easy_vector<T> &c) {
//                out << c.toString();
//                return out;
//        }
//
//    template<typename T>
//    void easy_vector<T>::sort (){
//        std::sort(begin(*this), end(*this));
//    }
//
//
//    template<typename T>
//    void easy_vector<T>::sort (std::function<  bool (T & a, T & b) > selector ){
//        std::sort(begin(this), end(this),selector);
//    }
//
//
//    template<typename T>
//    long easy_vector<T>::indexOf(T item){
//        long index = -1;
//        auto start = std::begin(*this);
//        auto end = std::end(*this);
//        auto it = std::find(start,end, item );
//        if ( it != end){
//           index= it - start;
//        }
//        return index;
//    }
//
//    template<typename T>
//    bool easy_vector<T>::removeFirstOccurrenceOfItem (T item){
//        // TODO : change signature to take a lambda that will be executed when occurrence is encountered
//        // TODO : with default null
//        auto it = std::find(std::begin(*this),std::end(*this),item);
//        if (it!=std::end(*this)){
//           this->erase(it);
//           return true;
//        }
//        return false;
//    }

//    template<typename T>
//    bool easy_vector<T>::removeLastOccurrenceOfItem (T item){
//        auto it = std::find(std::rbegin(*this),std::rend(*this),item);
//        if (it!=std::rend(*this)){
//            //this->erase(it);
//            return true;
//        }
//        return false;
//    }

}
