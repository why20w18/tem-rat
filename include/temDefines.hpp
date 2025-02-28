#ifndef __TEM_DEFINES_HPP__
#define __TEM_DEFINES_HPP__

    #ifdef CSOCK_PLATFORM_IS_UNIX
        #define TEM_HOST 0
    #endif 

    #ifdef CSOCK_PLATFORM_IS_WIN32
        #define TEM_HOST 1
    #endif 

enum TEM_BACKDOOR_MODES{
    BACKDOOR_REVERSE_SHELL,
    BACKDOOR_BIND_SHELL
};

enum TEM_ENCRYPT_TYPE{
    ENCRYPT_XOR,
    ENCRYPT_RSA
};

#endif // __TEM_DEFINES_HPP__