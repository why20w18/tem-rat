#ifndef __UTILS_HPP__
#define __UTILS_HPP__

#include <vector>
#include <stdio.h>
#include <stdlib.h>  

#include "temDefines.hpp"
#include "csockManuel.hpp"

#ifdef CSOCK_PLATFORM_IS_UNIX
    #include <ifaddrs.h>
#endif 

#ifdef CSOCK_PLATFORM_IS_WIN32  
    #include <iphlpapi.h>
    #pragma comment(lib, "IPHLPAPI.lib")
    
    #define MALLOC(x) HeapAlloc(GetProcessHeap(), 0, (x))
    #define FREE(x) HeapFree(GetProcessHeap(), 0, (x))
    
    using namespace std; 
#endif


//systemAccess.cpp
std::vector<std::vector<std::string>> utils_getLAN_IPV4(bool isPrintOut = false);


//


#endif //__UTILS_HPP__