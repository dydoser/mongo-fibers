#ifndef MONGODB_ASYNC_DBCONNECTIONPOOL_H
#define MONGODB_ASYNC_DBCONNECTIONPOOL_H

#include "MongoDbHeader.hpp"
#include "../mongo-fibers/DbWorker.hpp"
#include <thread>
#include "BasicHeader.hpp"
#include "DbSessionDelegate.hpp"
#include "ConcurrentQueue.hpp"
#include "DbSessionTask.hpp"

using namespace std;


class DbConnectionPool {
    vector<shared_ptr<DbWorker>> mWorkers;
    ConcurrentQueue<DbSessionTask*> mTasks;
public:
    DbConnectionPool(string uri, string db, int concurrencyLevel) {
        for(int i = 0; i < concurrencyLevel; ++i) {
            auto worker = make_shared<DbWorker>(mTasks, mongocxx::uri(uri), db);
            worker->start();
            mWorkers.push_back(move(worker));
        }
    }



    bool dbSession(DbSessionDelegate delegate) {
        return fibers::await([&](fibers::Promise<bool> promise) {
            DbSessionTask* task = new DbSessionTask();
            task->delegate = move(delegate);
            task->finishCallback = [promise(move(promise))](bool isErrorHappened) mutable {
                promise.setValue(isErrorHappened);
            };
            mTasks.push(task);
        });
    }

    DbConnectionPool operator= (DbConnectionPool& oth) = delete;
    ~DbConnectionPool() {
        for(auto workerPtr: mWorkers) {
            workerPtr->shutdown();
        }
    }
};

#endif //MONGODB_ASYNC_DBCONNECTIONPOOL_H