//
// Created by George Ford on 8/27/21.
//

#ifndef DOCUMENTSCANNER_DSUTILITIES_H
#define DOCUMENTSCANNER_DSUTILITIES_H

#include <iostream>
#include <queue>
#include <thread>
#include <chrono>

#define DEBUG_PRINT(var)	std::cout << (var) << ": Line: " << __LINE__ \
                                    << std::endl;

void spinWaiting(int ms, const bool& stop, std::string& message);

#endif //DOCUMENTSCANNER_DSUTILITIES_H
