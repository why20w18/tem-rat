#ifndef __TEM_RAT_HPP__
#define __TEM_RAT_HPP__

#include "csock.hpp"
#include "temDefines.hpp"

#include <vector>

class RatServer{
private:
    uint rsPortNo;
  
    struct sockaddr_in *ratServerConfig;

    csock *rs;
    std::string rsIPAddr;

    CSOCK_INIT init_rsIPV;
    CSOCK_INIT init_rsProtocol;
   
public:
    RatServer(uint rsPortNo,const std::string rsIPAddr,
              CSOCK_INIT ipv4_v6=IPV4, CSOCK_INIT tcp_udp = TCP , bool threaded = true,bool serverInputed = true);
              //tcp_ipv4 server baslatma
   
    bool compileExecutable();
            
    ~RatServer();


    


    
};


#endif 