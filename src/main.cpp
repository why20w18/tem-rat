#include "../include/csock.hpp"
#include "../include/utils.hpp"
#include <string>

using namespace std;

int main(){
    
    short no = -1;
    std::vector<string> selectedInterface(2);

    {
        std::vector<std::vector<std::string>> interfaceV4 = utils_getLAN_IPV4(true);
        cout << "[TEM-RAT-STARTER] : " << "select interface ip : ";
        cin >> no;
        if(no < 0 || no >= interfaceV4.size()){
            std::cerr << "INVALID CHOOSING !" << "\n"; 
            return 0x1;
        }
        selectedInterface[0] = string(interfaceV4[no][0]); //interface
        selectedInterface[1] = string(interfaceV4[no][1]); //ip
    }
    
    cout << selectedInterface[0] << "\n";
    cout << selectedInterface[1] << "\n";

    

    return 0x0;
}