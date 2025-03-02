//systemAccess.cpp
#include "../../include/utils.hpp"
#include <iomanip>

/*  
    CROSS PLATFORM
    1-server user LAN ipsi cekme
    2-server user PUBLIC ise port forwarding islemlerini yapma
*/

/*
    {   2D_ARRAY
        {INTERFACE_NAME0,IP_ADDR0},
        {INTERFACE_NAME1,IP_ADDR1}
    }
*/

std::vector<std::vector<std::string>> utils_getLAN_IPV4(bool isPrintOut){
     std::vector<std::vector<std::string>> interfaceIPV4(CSOCK_DEFAULT_IFADDRS_COUNT);

    #ifdef CSOCK_PLATFORM_IS_UNIX
        //linux icin derleme
        char ipAddr[CSOCK_IP_STRLEN];
        struct ifaddrs *head = NULL;
        struct ifaddrs *node = NULL;
        csockManuel *csock = new csockManuel;

        getifaddrs(&head);
        short i = 0;

        if (isPrintOut){
            std::cout << std::setw(10) << std::left << "No"
                      << std::setw(15) << std::left << "Interface"
                      << std::setw(20) << std::left << "IP Address" << "\n";
            std::cout << "--------------------------------------------" << "\n";
        }

        for(node = head ; node != NULL ; node = node->ifa_next){

            //ipv4 adresleri ayiklama
            if(node->ifa_addr->sa_family == IPV4){
                void *tempAddr = &((sockaddr_in*)(node->ifa_addr))->sin_addr;
                csock->csock_inetNtop(IPV4,tempAddr,ipAddr);

                if(isPrintOut){
                    std::cout << std::setw(10) << std::left << i
                              << std::setw(15) << std::left << node->ifa_name
                              << std::setw(20) << std::left << ipAddr << "\n";
                }

                interfaceIPV4[i].push_back(node->ifa_name);
                interfaceIPV4[i++].push_back(ipAddr);
                
            }

        }


        freeifaddrs(head);
        delete csock;
        interfaceIPV4.resize(i);

        return interfaceIPV4;
    #endif 

    #ifdef CSOCK_PLATFORM_IS_WIN32
        //kaynak msdn : https://learn.microsoft.com/en-us/windows/win32/api/iptypes/ns-iptypes-ip_adapter_info

        short i = 0;
    
        PIP_ADAPTER_INFO pAdapterInfo;
        PIP_ADAPTER_INFO pAdapter = NULL;
        DWORD dwRetVal = 0;
        
        if (isPrintOut){
            std::cout << std::setw(10) << std::left << "No"
                      << std::setw(15) << std::left << "Interface"
                      << std::setw(20) << std::left << "IP Address" << "\n";
            std::cout << "--------------------------------------------" << "\n";
        }

    
        ULONG ulOutBufLen = sizeof (IP_ADAPTER_INFO);
        pAdapterInfo = (IP_ADAPTER_INFO *) MALLOC(sizeof (IP_ADAPTER_INFO));
        if (pAdapterInfo == NULL) {
            printf("Error allocating memory needed to call GetAdaptersinfo\n");
        }
    
        if (GetAdaptersInfo(pAdapterInfo, &ulOutBufLen) == ERROR_BUFFER_OVERFLOW) {
            FREE(pAdapterInfo);
            pAdapterInfo = (IP_ADAPTER_INFO *) MALLOC(ulOutBufLen);
            if (pAdapterInfo == NULL) {
                printf("Error allocating memory needed to call GetAdaptersinfo\n");
            }
        }
    
        if ((dwRetVal = GetAdaptersInfo(pAdapterInfo, &ulOutBufLen)) == NO_ERROR) {
            pAdapter = pAdapterInfo;
            while (pAdapter){

                
                switch (pAdapter->Type) {
                case MIB_IF_TYPE_OTHER:
                if(isPrintOut)    
                printf("Other\t\t");
                    interfaceIPV4[i].push_back("Other");
                    break;
    
                case MIB_IF_TYPE_ETHERNET:
                if(isPrintOut)    
                printf("Ethernet\t\t");
                    interfaceIPV4[i].push_back("Ethernet");
                    break;
                
                case MIB_IF_TYPE_TOKENRING:
                if(isPrintOut)    
                printf("Token Ring\t\t");
                    interfaceIPV4[i].push_back("Token Ring");
                    break;
                
                case MIB_IF_TYPE_FDDI:
                if(isPrintOut)    
                printf("FDDI\t\t");
                    interfaceIPV4[i].push_back("FDDI");
                    break;
                
                case MIB_IF_TYPE_PPP:
                if(isPrintOut)
                    printf("PPP\t\t");
                    interfaceIPV4[i].push_back("PPP");
                    break;
                
                case MIB_IF_TYPE_LOOPBACK:
                if(isPrintOut)
                    printf("Loopback\t\t");
                    interfaceIPV4[i].push_back("Loopback");
                    break;
                
                case MIB_IF_TYPE_SLIP:
                if(isPrintOut)
                    printf("Slip\t\t");
                    interfaceIPV4[i].push_back("Slip");
                    break;
                
                default:
                if(isPrintOut)
                    printf("Unknown Type %ld\t\t", pAdapter->Type);
                    interfaceIPV4[i].push_back("Unknown Type");
                    break;
                }
    
            printf("\tIP Address: %s\n",pAdapter->IpAddressList.IpAddress.String);


               
            interfaceIPV4[i++].push_back(pAdapter->IpAddressList.IpAddress.String);        
            pAdapter = pAdapter->Next;
            }
        } 
        else
            printf("GetAdaptersInfo failed with error: %d\n", dwRetVal);
        
        
        if (pAdapterInfo)
            FREE(pAdapterInfo);
    
        return interfaceIPV4;
    #endif 
}