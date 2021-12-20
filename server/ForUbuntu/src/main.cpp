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

 for (int i = 1; i < argc; i++)
{  
  
        if (strcmp(argv[i], "-local") == 0)
        {       
            std::string ip = getMyIP();
            std::cout << "ip = "<<  getMyIP() << std::endl;         
            
        }
  if (strcmp(argv[i], "-h") == 0)
        {       
            std::cout << "help "<< std::endl;          
            
        }
    
      if (i + 1 != argc)
    {
        if (strcmp(argv[i], "-ip") == 0 && isIP(argv[i + 1])) // This is your parameter name
        {   
            std::string ip = argv[i + 1];
            std::cout << "ip = "<<  argv[i + 1] << std::endl;  // The next value in the array is your value
            i++;    // Move to the next flag
        }
    }
}

test ();

Chat *chat = new Chat; 

try{
    SocetServer *server = new SocetServer(*chat,ip);    
    server->init ();
    server->connect();
   // server->connect();
}
catch (const char* err ){
    std::cout << "\n=> "<< err << std::endl;
}


std::cout << "\n=> main" << std::endl;

return 0;
}