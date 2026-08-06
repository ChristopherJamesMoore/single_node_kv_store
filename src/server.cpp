#include "store.hpp"
#include "httplib.h"
#include <iostream>

int main() {
    Store store;
    store.openLog("kvstore.log");
    store.replayLog("kvstore.log");

    httplib::Server svr;

    svr.Get(R"(/v1/keys/(.+))", [&store](const httplib::Request& req, httplib::Response& res) {
        std::string key = req.matches[1];
        if (auto val = store.get(key)) {
            res.set_content(*val, "text/plain");
        } else {
            res.status = 404;
        }
    });

    svr.Put(R"(/v1/keys/(.+))", [&store](const httplib::Request& req, httplib::Response& res) {
        std::string key = req.matches[1];
        store.set(key, req.body);
        res.status = 200;
    });

    svr.Delete(R"(/v1/keys/(.+))", [&store](const httplib::Request& req, httplib::Response& res) {
        std::string key = req.matches[1];
        res.status = store.remove(key) ? 200 : 404;
    });

    std::cout << "Listening on http://localhost:8080\n";
    svr.listen("0.0.0.0", 8080);
}
