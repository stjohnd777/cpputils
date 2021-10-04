#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <functional>

namespace dsj {

    class StringUtils {

    public:
        /**
         End with suffix
         */
        static bool endsWith(const std::string &s, const std::string &suffix);

        /**
         Start with suffix
         */
        static bool startsWith(const std::string &s, const std::string &suffix);

        /**
         String s contains key
         */
        static bool contains(const std::string &s, const std::string &key);

        /**
         Replace all instances of target with repl in src
         */
        static std::string replaceAllSubstrings(std::string src, std::string const &target, std::string const &repl);

        /**
         Split
         */
        static void split(std::vector<std::string> &result, std::string str, char delim);

        /**
         Trim
         */
        static std::string trim(std::string s);

        /**
         Is white space
         */
        static bool isWhiteSpaceChar(const char c);
    };


    class easy_string : public std::string {
    public:

        easy_string(std::string s) ;

        /**  Ends with suffix  */
        bool endsWith(const std::string &suffix) ;

        /**  Start with suffix  */
        bool startsWith(const std::string &suffix) ;

        /**  Reverse the string  */
        void reverse();

        /** String s contains key  */
        bool contains(const std::string &key) ;

        ///  Returns the index within this string of the first occurrence of the specified charac
        int indexOf(int ch) ;
        
        // Returns the index within this string of the first occurrence of the
        // specified character, starting the search at the specified index.
        int indexOf(int ch, int fromIndex) ;
        
        //  Returns the index within this string of the first occurrence of the specified substring.
        int indexOf(std::string str) ;

        ///
        int indexOf(std::string str, int fromIndex) ;

        int next(std::string str, bool reset);

        /**  Replace all instances of target with repl in src */
        easy_string replaceAllSubstrings(std::string const &target, std::string const &repl) ;

        // Returns a string resulting from replacing all occurrences of oldChar
        // in this string with newChar.
        easy_string replace(char oldChar, char newChar) ;

        //  Replaces each substring of this string that matches the literal
        //  target sequence with the specified literal replacement sequence.
        easy_string replace(std::string target, std::string replacement) ;

        // At Every instance of 'c' invoke lamdba
        void invokeAt(char c, std::function<void(std::string::iterator pos, int index)> lambda) ;

        // At Every instance of 'part' invoke lamdba
        void invokeAt(std::string part, std::function<void(std::string::iterator pos, int index)> lambda) ;

        /** Split */
        std::vector<std::string> split(char delim);

        easy_string substring(int beginIndex, int endIndex) ;

        char * toCharArray() ;

        easy_string toUpperCase() ;

        easy_string toLowerCase() ;

        /**
         * Returns a string whose value is this string, with all leading and trailing space removed,
         * where space is defined as any character whose codepoint is less than or equal to 'U+0020'
         * (the space character).
         * @param s
         * @return
         */
        easy_string trim( ) ;

    };

}

