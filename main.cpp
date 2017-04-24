#include <iostream>
#include "DbConnectionPool.hpp"

DbConnectionPool db("mongodb://localhost:27017", "alien", 1);

int main(int, char**) {
    folly::EventBase evb;
    auto& fiberManager = folly::fibers::getFiberManager(evb);

    fiberManager.addTask([&](){
        db.dbSession([](mongocxx::client& client, mongocxx::database& defaultDb){
            cout << "lol" << endl;
            sleep(1);
        });
        cout << "lol2" << endl;
    });

    evb.loopForever();
}