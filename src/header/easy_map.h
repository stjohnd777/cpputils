//
// Created by Daniel St. John on 12/25/20.
//

#pragma once

#include <string>
#include <sstream>

#include <set>
#include <map>
#include <algorithm>

#include "easy_vector.h"
template<typename T,typename U>
class easy_map : public std::map<T,U>{
    
public:
    
    // TODO : DRY
    friend std::ostream &operator<<(std::ostream &out, const easy_map<T,U> &map);
    
    // TODO : DRY
    std::string  toString(){
        std::stringstream ss;
        ss << "{" ;
       forEach([&] (std::pair<T,U>  p){
            ss << "(" << p.first << ":" << p.second << ")" << std::endl;
        });
        ss << "}" << std::endl;
        return ss.str();
    }
    
    
    dsj::easy_vector< T> getKeys(){
        dsj::easy_vector< T>  keys;
        for (auto  it : *this) {
            keys.push_back(it.first);
        }
        return keys;
    }
    
    // TODO : easy_set
    dsj::easy_vector< T> getValues(){
        dsj::easy_vector<T> s;
        for (auto  it : *this) {
            s.push_back(it.second);
        }
        return s;
    }
    
    
    void forEach( std::function<  void(std::pair<T,U> & aPair)> selector) {
        std::for_each(this->begin(), this->end(), [&](std::pair<T,U> aPair) {
            selector(aPair);
        });
    }
    
    void forEachReverse( std::function<  void(std::pair<T,U> & aPair)> selector) {
        std::for_each(this->rbegin(), this->rend(), [&](std::pair<T,U> aPair) {
            selector(aPair);
        });
    }

    // TODO : keys are unique, so unique elements
    std::unique_ptr<std::map<T,U>>  unique() {
        std::unique_ptr< easy_map<T,U> > copy = this;
        // TODO
        return std::move( copy );
    }
    
    
    easy_map<T,U> filter( std::function<  bool(std::pair<T,U>  & element)> selector) {
       easy_map<T,U>  m ;
       std::for_each(begin(*this), end(*this), [&](std::pair<T,U> p) {
           if (selector(p)) {
               m [p.first] = p.second;
           }
       });
       return m;
   }
    
    template<typename TT, typename UU >
    easy_map<TT,UU>  map( std::function< std::pair<TT,UU>(std::pair<T,U> &oldPair)> transformer) {

        easy_map<TT,UU>  m ;
        this->forEach( [&](std::pair<T,U> p){
            auto newPair = transformer(p);
            m[newPair.first] = newPair.second;
        });
        return m;
    }
};


 
