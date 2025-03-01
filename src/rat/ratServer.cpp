#include "../../include/ratServer.hpp"

RatServer::RatServer(uint ratPort,const char *ratIP,TEM_TARGET_OS targetOs)
: ratPort(ratPort) , ratIP(ratIP){
    this->targetOs = targetOs;

}

bool RatServer::temReverseShell(){

    

    return false;
}