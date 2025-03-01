#ifndef __UTILS_HPP__
#define __UTILS_HPP__

#include <ifaddrs.h>
#include <vector>

#include "temDefines.hpp"
#include "csockManuel.hpp"

//systemAccess.cpp
std::vector<std::vector<std::string>> utils_getLAN_IPV4(bool isPrintOut = false);


//


#endif //__UTILS_HPP__