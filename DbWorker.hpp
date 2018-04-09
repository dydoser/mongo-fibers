//
// Created by origin on 30.10.16.
//

#ifndef MONGODB_ASYNC_DBWORKER_H
#define MONGODB_ASYNC_DBWORKER_H

#include "BasicHeader.hpp"
#include "ConcurrentQueue.hpp"
#include "DbSessionTask.hpp"

class DbWorker: public std::enable_shared_from_this<DbWorker> {
    ConcurrentQueue<DbSessionTask*>& mTasks;
    bool mStopFlag = false;
    void mTaskLoop() {
        auto destroyProtector = shared_from_this();
        while(!mStopFlag) {
            DbSessionTask* t = mTasks.pop();
            bool isErrorHappened = false;
            try {
                t->delegate(mClient, mDb);
            }
            catch(...) {
                isErrorHappened = true;
            }
            t->finishCallback(true);
            delete t;
        }
    }
    mongocxx::database mDb;
    mongocxx::client mClient;
public:
    DbWorker&operator=(const DbWorker& oth) = delete;
    DbWorker(ConcurrentQueue<DbSessionTask*>& _tasks, const mongocxx::uri _uri, string db): mDb(), mClient(_uri), mTasks(_tasks) {
        mDb = mClient[db];
    }
    void start() {
        thread(&DbWorker::mTaskLoop, this).detach();
    }
    void shutdown() {
        mStopFlag = true;
    }
};

#endif //MONGODB_ASYNC_DBWORKER_H
