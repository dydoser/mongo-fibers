#ifndef MONGODB_ASYNC_DBSESSIONTASK_HPP
#define MONGODB_ASYNC_DBSESSIONTASK_HPP

#include "DbSessionDelegate.hpp"
#include "BasicHeader.hpp"

class DbSessionTask {
public:
    DbSessionDelegate delegate;
    folly::Function<void(bool)> finishCallback;
};

#endif //MONGODB_ASYNC_DBSESSIONTASK_HPP
