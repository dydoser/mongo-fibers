cmake_minimum_required(VERSION 3.1)
project(mongo-fibers)

find_package(libmongocxx)
find_package(libbsoncxx)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -pthread -O3")

set(SOURCE_FILES ConcurrentQueue.hpp
        DbConnectionPool.hpp
        DbSessionDelegate.hpp
        DbWorker.hpp
        MongoDbHeader.hpp
        main.cpp
        DbSessionTask.hpp
        BasicHeader.hpp)
include_directories(mongo-fibers ${LIBMONGOCXX_INCLUDE_DIRS} ${LIBBSONCXX_INCLUDE_DIRS})
link_directories(mongo-fibers ${LIBMONGOCXX_LIBRARY_DIRS} ${LIBBSONCXX_LIBRARY_DIRS})
add_executable(mongo-fibers ${SOURCE_FILES})
target_link_libraries(mongo-fibers
        -lmongocxx
        -lbsoncxx
        ${Boost_LIBRARIES}
        -lfolly
        )