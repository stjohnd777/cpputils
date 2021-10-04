//
// Created by Daniel St. John on 10/3/21.
//

#pragma once

#include <iostream>
#include <sstream>
#include <algorithm>
#include <functional>
#include <chrono>
#include <ctime>

#include "crow_all.h"

using namespace std;
using namespace crow;

void info(std::string info) {
    auto timepoint = chrono::system_clock::now();
    auto tt = chrono::system_clock::to_time_t(timepoint);
    std::cout << ctime(&tt) << ":" << info << std::endl;
}

class RestServer {

public :
    RestServer(int port) {}

    void start() {

        CROW_ROUTE(app, "/")
                ([](const request &req, response &res) {
                    info("route : / : defaults to /index sendHTML(index) => index.html");
                    sendHTML(res, "index");
                });

        CROW_ROUTE(app, "/css/<string>")
                ([](const request &req, response &res, string filename) { sendCSS(res, filename); });

        CROW_ROUTE(app, "/js/<string>")
                ([](const request &req, response &res, string filename) { sendScript(res, filename); });

        CROW_ROUTE(app, "/image/<string>")
                ([](const request &req, response &res, string filename) {
                    sendImage(res, filename);
                });

        CROW_ROUTE(app, "/json/<string>")
                ([](const request &req, response &res, string filename) {
                    sendJSON(res, filename);
                });

        CROW_ROUTE(app, "/add_json")
                .methods("POST"_method)
                        ([](const crow::request &req) {
                            auto x = crow::json::load(req.body);
                            if (!x) {
                                return crow::response(400);
                            }
                            int sum = x["a"].i() + x["b"].i();
                            std::ostringstream os;
                            os << sum;
                            return crow::response{os.str()};
                        });


        auto port = getPort();
        app.port(port).multithreaded().run();
        std::cout << "Running on port " << port << std::endl;

    }

protected:

    crow::SimpleApp app;

    bool endsWith(const std::string &str, const std::string &suffix) {
        return str.size() >= suffix.size() && 0 == str.compare(str.size() - suffix.size(), suffix.size(), suffix);
    }

    void useExtension(response &res, string relativePath) {
        if (endsWith(relativePath, ".js")) {
            sendScript(res, relativePath);
            return;
        }
        if (endsWith(relativePath, ".css")) {
            sendCSS(res, relativePath);
            return;
        }
        if (endsWith(relativePath, ".html")) {
            sendHTML(res, relativePath);
            return;
        }
        if (endsWith(relativePath, ".jpeg")) {
            sendImage(res, relativePath);
            return;
        }
        sendFile(res, relativePath, "");
    }

    void sendFile(response &res, string relativePath, string contentType) {

        info("sendfile " + relativePath + " :" + contentType);
        std::string path = PUBLIC_HTML_DIR + "public" + "/" + relativePath;
        info("relative path " + path);

        ifstream in(path, ifstream::in);
        if (in) {
            stringstream contents;
            contents << in.rdbuf();
            in.close();
            res.write(contents.str());
            info(contents.str());
            res.set_header("Content-Type", contentType);
            res.code = 200;
        } else {
            res.write("404 file not found");
            res.code = 404;
            res.write("404 NOT FOUND");
        }
        res.end();
    }

    void sendCSS(response &res, string relativePath) {
        sendFile(res, "css/" + relativePath, "text/css");
    }

    void sendHTML(response &res, string relativePath) {
        sendFile(res, relativePath + ".html", "text/html");
    }

    void sendImage(response &res, string relativePath) {
        sendFile(res, "image/" + relativePath, "image/jpeg");
    }

    void sendScript(response &res, string relativePath) {
        sendFile(res, "js/" + relativePath, "text/javascript");
    }

    void sendJSON(response &res, string relativePath) {
        sendFile(res, "json/" + relativePath, "text/json");
    }

    std::string ReadTextFile(std::string path) {
        stringstream contents;
        ifstream in(path, ifstream::in);
        if (in) {
            contents << in.rdbuf();
            in.close();
        }
        return contents.str()
    }

private:

    std::string PUBLIC_HTML_DIR;

    int port;

    int getPort() {
        auto port = getenv("PORT");
        uint16_t iPort = static_cast<uint16_t>(port != NULL ? stoi(port) : 2222);
        return iPort;
    }

    std::string getPublic() {
        auto pub = getenv("PUBLIC");
        std::string PUBLIC = pub != nullptr ? pub : "../";
        return PUBLIC;
    }

};




















