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
    char ipAddr[CSOCK_IP_STRLEN];
    std::vector<std::vector<std::string>> interfaceIPV4(CSOCK_DEFAULT_IFADDRS_COUNT);

    if(TEM_HOST == 0){
        //linux icin derleme
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

        return interfaceIPV4;
    }
    else if(TEM_HOST == 1){
        //windows icin derleme

    }
}

