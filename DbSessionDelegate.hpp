#ifndef DBSESSIONDELEGATE_HPP
#define DBSESSIONDELEGATE_HPP


using DbSessionDelegate = function<void(mongocxx::client& client, mongocxx::database& defaultDb)>;

#endif