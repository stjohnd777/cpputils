

#include "../header/easy_string.h"

#include <iostream>
#include <functional>
#include <array>
#include <vector>
#include <map>
#include <algorithm>
#include <memory>
#include <random>       // std::default_random_engine
#include <chrono>       // std::chrono::system_clock
#include <string>
#include <sstream>

namespace dsj {

    bool StringUtils::endsWith(const std::string& s, const std::string& suffix)
    {
        return s.rfind(suffix) == (s.size()-suffix.size());
    }

    bool StringUtils::startsWith(const std::string& s, const std::string& prefix)
    {
        if ( s.length() < prefix.length() )
        {
            return false;
        }
        std::string front = s.substr(0,prefix.length());
        if ( front == prefix)
        {
            return true;
        }
        return false;
    }
    bool StringUtils::contains(const std::string& s, const std::string& key)
    {
        auto found = s.rfind(key);
        bool ret = ( found != std::string::npos );
        return ret;
    }
    std::string StringUtils::replaceAllSubstrings( std::string src, std::string const& target, std::string const& repl)
    {
        // handle error situations/trivial cases
        
        if (target.length() == 0)
        {
            // searching for a match to the empty string will result in
            //  an infinite loop
            //  it might make sense to throw an exception for this case
            return src;
        }
        
        if (src.length() == 0)
        {
            return src;  // nothing to match against
        }
        
        size_t idx = 0;
        
        for (;;)
        {
            idx = src.find( target, idx);
            if (idx == easy_string::npos)  break;
            
            src.replace( idx, target.length(), repl);
            idx += repl.length();
        }
        
        return src;
    }
    
    void StringUtils::split(std::vector<std::string> &result, std::string str, char delim )
    {
        std::string tmp;
        std::string::iterator i;
        result.clear();
        
        for(i = str.begin(); i <= str.end(); ++i)
        {
            if((const char)*i != delim  && i != str.end())
            {
                tmp += *i;
            }
            else
            {
                if ( !tmp.empty() ) {
                    result.push_back(tmp);
                }
                tmp = "";
            }
        }
    }

    std::string StringUtils::trim(std::string s)
    {
        char const *str = s.c_str();
        // Trim leading non-letters
        while(! StringUtils::isWhiteSpaceChar(*str))
        {
            str++;
        }
        // Trim trailing non-letters
        char const * end =(char const *) (str + s.length() - 1);
        while(end > str && !StringUtils::isWhiteSpaceChar(*end))
        {
            end--;
        }
        
        return std::string(str, end+1);
    }
    
    bool StringUtils::isWhiteSpaceChar(const char c)
    {
        bool ret = false;
        if (c==' ' || c=='\n' || c=='\t')
        {
            ret = true;
        }
        return ret;
    }



    easy_string::easy_string(std::string s) : std::string(s) {}



    bool easy_string::endsWith(const std::string &suffix) {
        return StringUtils::endsWith(*this, suffix);
    }

    /**
     Start with suffix
     */
    bool easy_string::startsWith(const std::string &suffix) {
        return StringUtils::startsWith(*this, suffix);
    }

    void easy_string::reverse(){
        std::reverse((*this).begin(), (*this).end());
    }

    /**
     String s contains key
     */
    bool easy_string::contains(const std::string &key) {
        return StringUtils::contains(*this, key);
    }


    ///  Returns the index within this string of the first occurrence of the specified charac
    int easy_string::indexOf(int ch) {
        return 0;
    }

    // Returns the index within this string of the first occurrence of the specified character, starting the search at the specified index.
    int easy_string::indexOf(int ch, int fromIndex) {
        return this->find(ch, 0);
    }

    //  Returns the index within this string of the first occurrence of the specified substring.
    int easy_string::indexOf(std::string str) {
        return this->find(str, 0);
    }

    ///
    int easy_string::indexOf(std::string str, int fromIndex) {
        return this->find(str, fromIndex);
    }

    int easy_string::next(std::string str, bool reset) {
        static int last = 0;
        if (reset) last = 0;
        last = this->find(str, last);
        if (last == std::string::npos) {
            last = 0;
        }
        return last;
    }

    /**
     Replace all instances of target with repl in src
     */
    //std::string
    easy_string easy_string::replaceAllSubstrings(
                   std::string const &target, std::string const &repl) {
        return StringUtils::replaceAllSubstrings(*this, target, repl);
    }

    // Returns a string resulting from replacing all occurrences of oldChar
    // in this string with newChar.
    easy_string easy_string::replace(char oldChar, char newChar) {
        return *this;
    }



    easy_string easy_string::replace(std::string target, std::string replacement) {
        return *this;
    }

    void easy_string::invokeAt(char c, std::function<void(std::string::iterator pos, int index)> lambda) {
        auto it = std::begin(*this);
        for (int index = 0; it != std::end(*this); it++) {
            if (*it == c) {
                lambda(it, index);
            }
            index++;
        }
    }

    void easy_string::invokeAt(std::string part, std::function<void(std::string::iterator pos, int index)> lambda) {
        int index = this->find(part);
    }


    std::vector<std::string> easy_string::split(char delim) {
        std::vector<std::string> result;
        StringUtils::split(result, *this, delim);
        return result;
    }

    easy_string easy_string::substring(int beginIndex, int endIndex) {
        auto sub = this->substr(beginIndex, endIndex);
        return easy_string(sub);
    }

    char *  easy_string::toCharArray() {
        char *ptr = &(*this)[0];
        return ptr;
    }

    easy_string easy_string::toUpperCase() {
        std::transform(this->begin(), this->end(), this->begin(), ::toupper);
        return *this;
    }

    easy_string easy_string::toLowerCase() {
        std::transform(this->begin(), this->end(), this->begin(), ::tolower);
        return *this;
    }


    easy_string easy_string::trim( ) {
        return StringUtils::trim(*this);
    }



}
