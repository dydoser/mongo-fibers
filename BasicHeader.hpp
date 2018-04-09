#ifndef CONVSERV__BASEHEADER_H
#define CONVSERV__BASEHEADER_H

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <math.h>
#include <string>
#include <sstream>
#include <thread>
#include "boost/shared_ptr.hpp"
#include <memory>
#include "boost/optional.hpp"

using std::thread;
using std::vector;
using std::map;
using std::string;
using std::pair;
using std::cout;
using std::cerr;
using std::endl;
using std::shared_ptr;
using std::make_shared;
using std::function;
using std::move;
using boost::optional;

#include "folly/fibers/Fiber.h"
#include "folly/fibers/EventBaseLoopController.h"
#include "folly/fibers/FiberManagerMap.h"

using namespace folly;

#endif //CONVSERV_BASEHEADER_H
