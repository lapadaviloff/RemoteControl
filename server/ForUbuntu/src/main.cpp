/**
* сервер для удаленного управления клавиатурой с телефона 
* 27.09.2021
* 
* Mitroshin Aleksey (miam.devsoft@yandex.ru, lapadaviloff@yandex.ru)
*/

#include <iostream>
#include "include/test.h"
#include "include/socetServer.h"
#include "include/chat.h"
#include "include/observer.h"
#include "include/getMyIP.h"
#include "include/isIP.h"



int Observer::m_staticNumber = 0;


int main (int argc, char * argv[]){
std::string ip ="";

 for (int i = 1; i < argc; i++){  
  
    if (strcmp(argv[i], "-local") == 0){       
            
            std::string ip = getMyIP();
            std::cout << "ip = "<<  getMyIP() << std::endl;         
            
        }
   if (strcmp(argv[i], "-h") == 0){       
           
            std::cout << "help "<< std::endl;          
            
        }
    
   if (i + 1 != argc){
        if (strcmp(argv[i], "-ip") == 0 && isIP(argv[i + 1])){ // This is your parameter name
           
            std::string ip = argv[i + 1];
            std::cout << "ip = "<<  argv[i + 1] << std::endl;  // The next value in the array is your value
            i++;    // Move to the next flag
        }
    }
}

test ();
std::cout <<"=> my IP : " <<  getMyIP() << std::endl; 
Chat *chat = new Chat; 
int buffer = 1024;
char * fromClient = new char [buffer];
char * toClient = new char [buffer];
strcpy(toClient," massage from server");
try{
    SocetServer *server = new SocetServer (
    *chat,
    fromClient,
    toClient,
    buffer);    
    
    do{
    server->connect();
    server->send_recerv();
    } while(1);
   
}
catch (const char* err ){
    std::cout << "\n=> "<< err << std::endl;
  
}
delete chat;
delete [] fromClient;
delete [] toClient;

std::cout << "\n=> main" << std::endl;

return 0;
}