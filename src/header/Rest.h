//
// Created by Daniel St. John on 9/30/21.
//

#pragma  once

#include <string>
#include <curl/curl.h>
#include <mutex>
#include <functional>


namespace dsj {

    class RestClient {
    public:
        std::string get (std::string uri);
        void get(std::string uri, std::function< void(std::string) > f);

        std::string post (std::string uri, const char *payload);
        RestClient();
    private:
        void validate(CURL *curl);
        void validate( CURLcode ret);
     };
}


